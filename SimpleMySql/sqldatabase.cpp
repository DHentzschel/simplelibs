#include "sqldatabase.h"

#include <mysql.h>

#include <logger.h>

#include "sqlquery.h"
#include "sqlutils.h"

AVector<SqlDatabase*> SqlDatabase::databases_;

#pragma warning (disable : 4251)
struct SqlDatabasePrivate {
	SqlDatabasePrivate();

    SqlDatabasePrivate(const SqlDatabasePrivate& database);

    MYSQL* mysql;

    bool isInList;

    bool isOpen;

    AString connectionName;

    AString hostname;

    ushort port;

    AString username;

    AString password;

    AString databaseName;

    AVector<std::shared_ptr<SqlTable>> tables;
};
#pragma warning (default: 4251)

SqlDatabasePrivate::SqlDatabasePrivate() :
	isInList(false),
	isOpen(false),
	mysql(nullptr),
	port(0)
{
}

/**
 * \brief Copies values of one instance to this new one.
 * \param database copyable instance
 */
SqlDatabasePrivate::SqlDatabasePrivate(const SqlDatabasePrivate& database) :
    // NOLINT(modernize-use-equals-default)
    mysql(database.mysql),
    isInList(database.isInList),
    isOpen(database.isOpen),
    connectionName(database.connectionName),
    hostname(database.hostname),
    port(database.port),
    username(database.username),
    password(database.password),
    databaseName(database.databaseName),
    tables(database.tables)
{}

/**
 * \brief Constructs new instance, sets connectionName passed by param and also sets default values.
 * Also adds this pointer to database list.
 * \param connectionName database connection name
 */
SqlDatabase::SqlDatabase(const AString& connectionName) :
    private_(new SqlDatabasePrivate())
{
    private_->mysql = mysql_init(nullptr);
    private_->isInList = false;
    private_->isOpen = false;
    private_->connectionName = connectionName;
    private_->port = 0;
    addToList(this);
}

/**
* \brief Copies values of one instance to this new one.
* \param database copyable instance
*/
SqlDatabase::SqlDatabase(const SqlDatabase& database) :
    private_(new SqlDatabasePrivate(*database.private_))
{
    private_->mysql = database.private_->mysql;
    private_->isInList = database.private_->isInList;
    private_->isOpen = database.private_->isOpen;
    private_->port = database.private_->port;
}

/**
* \brief Destroys current instance after closing database,
* removing this pointer from list and deleting private pointer.
*/
SqlDatabase::~SqlDatabase()
{
    close();
    removeFromList(this);
    delete private_;
}

/**
 * \brief Tries to open database connection by params,
 * reads all tables and their columns and returns success.
 * \return success
 */
bool SqlDatabase::open() const
{
    if (!mysql_real_connect(
        private_->mysql, private_->hostname.c_str(),
        private_->username.c_str(), private_->password.c_str(),
        private_->databaseName.c_str(), private_->port, nullptr, 0)) {
        Logger::error(getLastError());
        close();
        return private_->isOpen;
    }
    readTables();

	private_->isOpen = true;
    return private_->isOpen;
}

bool SqlDatabase::open(const AString& hostname,
    const ushort port,
    const AString& username,
    const AString& password,
    const AString& databaseName) const
{
    setHostname(hostname);
    setPort(port);
    setUsername(username);
    setPassword(password);
    return setDatabaseName(databaseName) && open();
}

/**
 * \brief Switches from one database to another.
 * \param databaseName database to switch to
 */
void SqlDatabase::switchDatabase(const AString& databaseName) const
{
    setDatabaseName(private_->databaseName);
    mysql_select_db(private_->mysql, private_->databaseName.c_str());
}

/**
 * \brief Closes current database connection.
 */
void SqlDatabase::close() const
{
    if (private_->isOpen && private_->mysql) {
        mysql_close(private_->mysql);
        private_->isOpen = false;
    }
}

/**
 * \brief Returns if current database connection is open.
 * \return if connection is open
 */
bool SqlDatabase::isOpen() const
{
    return private_->isOpen;
}

/**
 * \brief Returns current database connectionName.
 * \return connectionName
 */
AString SqlDatabase::getConnectionName() const
{
    return private_->connectionName;
}

/**
 * \brief Returns current hostname.
 * \return hostname
 */
AString SqlDatabase::getHostname() const
{
    return private_->hostname;
}

/**
 * \brief Sets current hostname and reconnects if connection initially was opened.
 * \param value new hostname
 */
void SqlDatabase::setHostname(const AString& value) const
{
    const auto wasOpen = private_->isOpen;
    if (wasOpen) {
        close();
    }
    private_->hostname = value;
    if (wasOpen) {
        open();
    }
}

/**
 * \brief Returns current port.
 * \return port
 */
ushort SqlDatabase::getPort() const
{
    return private_->port;
}

/**
* \brief Sets current port and reconnects if connection initially was opened.
* \param value new port
*/
void SqlDatabase::setPort(const ushort value) const
{
    const auto wasOpen = private_->isOpen;
    if (wasOpen) {
        close();
    }
    private_->port = value;
    if (wasOpen) {
        open();
    }
}

/**
 * \brief Returns current username.
 * \return username
 */
AString SqlDatabase::getUsername() const
{
    return private_->username;
}

/**
* \brief Sets current username and reconnects if connection initially was opened.
* \param value new username
*/
void SqlDatabase::setUsername(const AString& value) const
{
    const auto wasOpen = private_->isOpen;
    if (wasOpen) {
        close();
    }
    private_->username = value;
    if (wasOpen) {
        open();
    }
}

/**
 * \brief Returns current password.
 * \return password
 */
AString SqlDatabase::getPassword() const
{
    return private_->password;
}

/**
* \brief Sets current password and reconnects if connection initially was opened.
* \param value new password
*/
void SqlDatabase::setPassword(const AString& value) const
{
    const auto wasOpen = private_->isOpen;
    if (wasOpen) {
        close();
    }
    private_->password = value;
    if (wasOpen) {
        open();
    }
}

/**
 * \brief Returns current databaseName.
 * \return databaseName
 */
AString SqlDatabase::getDatabaseName() const
{
    return private_->databaseName;
}

/**
* \brief Sets current password and reconnects if connection initially was opened.
* \param value new password
*/
bool SqlDatabase::setDatabaseName(const AString& value) const
{
    const auto wasOpen = private_->isOpen;
    if (wasOpen) {
        close();
    }
    private_->databaseName = value;
    if (wasOpen) {
        return open();
    }
    return true;
}

/**
 * \brief Returns last MySql error as string.
 * \return last mysql error
 */
AString SqlDatabase::getLastError() const
{
    return mysql_error(private_->mysql);
}

/**
 * \brief Reads tables of current database.
 * Calls readTableTypes to get each column type,
 * name and length of every table.
 */
void SqlDatabase::readTables() const
{
    private_->tables = AVector<std::shared_ptr<SqlTable>>();
    mysql_query(private_->mysql, "SHOW TABLES");
    const auto res = mysql_store_result(private_->mysql);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        SqlTable table;
        table.name = row[0];
        private_->tables.append(std::make_shared<SqlTable>(table));
    }
    readTableTypes();
}

/**
 * \brief Serializes each column type,
 *  name and length of every table.
 */
void SqlDatabase::readTableTypes() const
{
    for (auto& i : private_->tables) {
        auto& table = *i;
        mysql_query(private_->mysql, AString("DESCRIBE " + table.name).c_str());
        auto* result = mysql_store_result(private_->mysql);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            if (mysql_field_count(private_->mysql) >= 2) {
                SqlColumn column;
                column.name = AString(row[0]);
                column.type = SqlUtils::getMySqlType(row[1]);
                column.length = SqlUtils::getMySqlLength(row[1]);
                table.columns.append(column);
            }
        }
    }
}

/**
 * \brief Returns current mysql struct pointer.
 * \return current mysql struct pointer
 */
MYSQL* SqlDatabase::getMySql() const
{
    return private_->mysql;
}

/**
 * \brief Returns all sql tables in a vector.
 * \return tables
 */
AVector<std::shared_ptr<SqlTable>>& SqlDatabase::getTables() const
{
    return private_->tables;
}

/**
 * \brief Adds new database instance with connectionName passed by param.
 * \param connectionName database connection name
 * \return reference to new database instance
 */
SqlDatabase SqlDatabase::addDatabase(const AString& connectionName)
{
    return SqlDatabase(connectionName);
}

/**
 * \brief Removes database with connectionName equal to passed param connectionName.
 * \param connectionName database connection name
 */
void SqlDatabase::removeDatabase(const AString& connectionName)
{
    databases_.removeFirst(findFromList(connectionName));
}

/**
 * \brief Returns pointer to database with connectionName equals to passed parama connectionName.
 * \param connectionName database connection name
 * \return database pointer
 */
SqlDatabase* SqlDatabase::database(const AString& connectionName)
{
    return findFromList(connectionName);
}

/**
 * \brief Adds pointer to database instance passed by param to database list.
 * \param database pointer to database instance
 * \return if added (was not in list) or not (was already in list)
 */
bool SqlDatabase::addToList(SqlDatabase* database)
{
    if (!database->private_->isInList) {
        if (findFromList(database->private_->connectionName) == nullptr) {
            database->private_->isInList = true;
            databases_.append(database);
            return true;
        }
    }
    return false;
}

/**
 * \brief Tries to remove pointer to database instance passed by param database and returns success
 * \param database pointer to database instance
 * \return success
 */
bool SqlDatabase::removeFromList(SqlDatabase* database)
{
    SqlDatabase* sqlDatabase;
    const auto oldSize = databases_.size();
    if (database->private_->isInList &&
        (sqlDatabase = findFromList(database->private_->connectionName)) !=
        nullptr) {
        sqlDatabase->private_->isInList = false;
        databases_.removeAll(sqlDatabase);
    }
    return databases_.size() != oldSize;
}

/**
 * \brief Searches for database with connectionName equals connectionName passed by param.
 * \param connectionName database connection name
 * \return nullptr if not found, pointer otherwise
 */
SqlDatabase* SqlDatabase::findFromList(const AString& connectionName)
{
    for (auto* database : databases_) {
        if (database->private_->connectionName == connectionName) {
            return database;
        }
    }
    return nullptr;
}
