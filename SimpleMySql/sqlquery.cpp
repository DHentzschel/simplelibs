#include "sqlquery.h"

#include <mysql.h>

#include <logger.h>

#include "psqltp.h"

// 4302 truncation from 'type 1' to 'type 2'
// 4311 pointer truncation from 'type' to 'type'
//#pragma warning(disable : 4302 4311)

struct SqlQueryPrivate {
	SqlQueryPrivate();

	SqlQueryPrivate(const SqlQueryPrivate& query);

	bool executedPrepared;

	bool nextOnError;

	SqlDatabase* database;

	std::shared_ptr<MYSQL_STMT> statement;

	AVector<MYSQL_BIND> parameters;

	AVector<std::shared_ptr<void>> parameterValues;

	MYSQL_BIND* results;

	MYSQL_RES* lastResult;

	MYSQL_ROW lastRow;

	std::shared_ptr<SqlTable> parsedQuery;

	uint64 recordCount;

	AString query;

	bool isSelectCommand;

	bool countRows;
};

SqlQueryPrivate::SqlQueryPrivate() :
	recordCount(0),
	lastRow(MYSQL_ROW()),
	executedPrepared(false),
	nextOnError(false),
	database(nullptr),
	results(nullptr),
	lastResult(nullptr),
	isSelectCommand(false),
	countRows(true)
{}

/**
 * \brief Constructs instance by copying from instance passed by param query.
 * \param query copyable instance
 */
SqlQueryPrivate::SqlQueryPrivate(const SqlQueryPrivate& query) :
	executedPrepared(query.executedPrepared),
	nextOnError(query.nextOnError),
	database(query.database),
	statement(query.statement),
	parameters(query.parameters),
	parameterValues(query.parameterValues),
	results(query.results),
	lastResult(query.lastResult),
	lastRow(query.lastRow),
	parsedQuery(query.parsedQuery),
	recordCount(query.recordCount),
	query(query.query),
	isSelectCommand(query.isSelectCommand),
	countRows(query.countRows)
{}

/**
 * \brief Constructs instance by passed param connectionName.
 * \param connectionName database connectionName to associate to database
 */
SqlQuery::SqlQuery(const AString& connectionName) :
	private_(new SqlQueryPrivate())
{
	private_->database = SqlDatabase::database(connectionName);
	clear();
}

/**
 * \brief Constructs instance by copying passed param query.
 * \param query copyable instance
 */
SqlQuery::SqlQuery(const SqlQuery& query) :
	private_(query.private_)   // NOLINT(modernize-use-equals-default)
{}

/**
 * \brief Destroys instance after calling clear() and deleting private pointer;
 */
SqlQuery::~SqlQuery()
{
	clear();
	delete private_;
}

/**
 * \brief Adds a bindable value by passed param value.
 * \param value sqlvariantparam
 */
void SqlQuery::addBindValue(const SqlVariantParam& value) const
{
	auto fieldType = MYSQL_TYPE_NULL;
	my_bool isUnsigned = TRUE;
	uint bufferLength = 0;

	AString str;
	switch (value.index()) {
	case SqlChar:
	{
		isUnsigned = 0;
		const auto val = std::get<char>(value);
		auto* pData = new char[1];
		pData[0] = val;
		str = std::to_string(val);
		private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::shared_ptr<char>(
			pData, [](const char* value) { delete[] value; })));
		bufferLength = sizeof(char);
	}
	case SqlBool:
	{
		if (str.empty()) {
			auto val = std::get<bool>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<bool>(val)));
			bufferLength = sizeof(bool);
		}
	}
	case SqlByte:
	{
		fieldType = MYSQL_TYPE_TINY;
		if (str.empty()) {
			auto val = std::get<byte>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<byte>(val)));
			bufferLength = sizeof(byte);
		}
		break;
	}
	case SqlShort:
	{
		isUnsigned = 0;
		if (str.empty()) {
			auto val = std::get<short>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<short>(val)));
			bufferLength = sizeof(short);
		}
	}
	case SqlUShort:
	{
		fieldType = MYSQL_TYPE_SHORT;
		if (str.empty()) {
			auto val = std::get<ushort>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<ushort>(val)));
			bufferLength = sizeof(ushort);
		}
		break;
	}
	case SqlInt:
	{
		isUnsigned = 0;
		if (str.empty()) {
			auto val = std::get<int>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<int>(val)));
			bufferLength = sizeof(int);
		}
	}
	case SqlUInt:
	{
		fieldType = MYSQL_TYPE_LONG;
		if (str.empty()) {
			auto val = std::get<uint>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<uint>(val)));
			bufferLength = sizeof(uint);
		}
		break;
	}
	case SqlInt64:
	{
		isUnsigned = 0;
		if (str.empty()) {
			auto val = std::get<int64>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<int64>(val)));
			bufferLength = sizeof(int64);
		}
	}
	case SqlUInt64:
	{
		fieldType = MYSQL_TYPE_LONGLONG;
		if (str.empty()) {
			auto val = std::get<uint64>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<uint64>(val)));
			bufferLength = sizeof(uint64);
		}
		break;
	}
	case SqlFloat:
	{
		isUnsigned = 0;
		fieldType = MYSQL_TYPE_FLOAT;
		if (str.empty()) {
			auto val = std::get<float>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<float>(val)));
			bufferLength = sizeof(float);
		}
		break;
	}
	case SqlDouble:
	{
		isUnsigned = 0;
		fieldType = MYSQL_TYPE_DOUBLE;
		if (str.empty()) {
			auto val = std::get<double>(value);
			str = std::to_string(val);
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(std::make_shared<double>(val)));
			bufferLength = sizeof(double);
		}
		break;
	}
	case SqlCharPtr:
	{
		isUnsigned = 0;
		fieldType = MYSQL_TYPE_STRING;
		if (str.empty()) {
			const auto val = const_cast<char*>(std::get<const char*>(value));
			str = val;
			private_->parameterValues.append(
				std::reinterpret_pointer_cast<void>(std::shared_ptr<char>(
					_strdup(val), [](const char* d) { delete[] d; })));
			bufferLength = static_cast<uint>(strlen(val));   // Todo Insecure
		}
		break;
	}
	case SqlString:
	{
		isUnsigned = 0;
		fieldType = MYSQL_TYPE_STRING;
		if (str.empty()) {
			AString val = std::get<AString>(value);
			str = val;
			private_->parameterValues.append(std::reinterpret_pointer_cast<void>(
				std::shared_ptr<char>(_strdup(val.c_str()), [](const char* d) { delete[] d; })));
			bufferLength = static_cast<uint>(val.length());
		}
		break;
	}
	default:
		break;
	}

	addBindValue(fieldType, private_->parameterValues.at(private_->parameterValues.size() - 1).get(),
		isUnsigned, bufferLength);
}

/**
 * \brief Prepares query string for executing.
 * \param query query string to prepare
 * \return success
 */
bool SqlQuery::prepare(const AString & query) const
{
	clear();

	if (!private_->database || !private_->database->isOpen()) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__,
			"Database is not opened.");
		return false;
	}

	if (private_->countRows) {
		countRows(query);
	}

	private_->query = query;
	private_->statement = std::shared_ptr<MYSQL_STMT>(
		mysql_stmt_init(private_->database->getMySql()), [](MYSQL_STMT*) {});

	if (mysql_stmt_prepare(private_->statement.get(), private_->query.toCString(),
		static_cast<uint>(private_->query.size()))) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	private_->parameters.reserve(private_->query.count("?"));
	return true;
}

/**
 * \brief Tries to execute prepared query and returns success.
 * \return success
 */
bool SqlQuery::exec() const
{
	private_->executedPrepared = true;

	if (!private_->database || !private_->database->isOpen()) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__,
			"Database is not opened.");
		return false;
	}

	if (mysql_stmt_bind_param(private_->statement.get(),
		private_->parameters.data())) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	private_->parsedQuery = parseQuery();
	private_->results = new MYSQL_BIND[private_->parsedQuery->columns.size()];

	ZeroMemory(private_->results,
		sizeof(MYSQL_BIND) * private_->parsedQuery->columns.size());

	for (size_t i = 0; i < private_->parsedQuery->columns.size(); ++i) {
		private_->results[i].buffer_type = static_cast<enum_field_types>(private_->parsedQuery->columns[i].type);
		private_->results[i].buffer_length = private_->parsedQuery->columns[i].length;
		private_->results[i].buffer = new char[static_cast<size_t>(private_->results[i].buffer_length) + 1];
		ZeroMemory(private_->results[i].buffer, static_cast<size_t>(private_->results[i].buffer_length) + 1);
	}

	if (private_->isSelectCommand && mysql_stmt_bind_result(private_->statement.get(), private_->results)) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	if (mysql_stmt_execute(private_->statement.get())) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	return true;
}

/**
 * \brief Tries to execute a NON-prepared query and returns success.
 * \param query query string to execute
 * \return success
 */
bool SqlQuery::exec(const AString & query) const
{
	clear();
	if (!private_->database || !private_->database->isOpen()) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__,
			"Database is not opened.");
		return false;
	}

	if (private_->countRows) {
		countRows(query);
	}
	auto recordCount = private_->recordCount;
	clear();
	private_->recordCount = recordCount;
	private_->executedPrepared = false;
	private_->query = query;
	private_->parsedQuery = parseQuery();

	auto result = !mysql_query(private_->database->getMySql(), query.c_str());
	private_->lastResult = mysql_store_result(private_->database->getMySql());
	if (private_->isSelectCommand) {
		return private_->lastResult&& result;
	}
	return result;
}

/**
 * \brief Tries to fetch next row and returns if the was a next.
 * \return if next is reachable
 */
bool SqlQuery::next() const
{
	if (!private_->database || !private_->database->isOpen()) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__,
			"Database is not opened.");
		private_->nextOnError = true;
		return false;
	}
	if (!private_->nextOnError && private_->executedPrepared) {
		if (mysql_stmt_fetch(private_->statement.get()) != MYSQL_NO_DATA) {
			return true;
		}
	}
	else {
		if (!private_->nextOnError && private_->lastResult) {
			if ((private_->lastRow = mysql_fetch_row(private_->lastResult))) {
				return true;
			}
		}
	}
	private_->nextOnError = true;
	return false;
}

/**
 * \brief Returns value from column passed by param column as variant.
 * \param column column name
 * \return value as variant
 */
SqlVariant SqlQuery::value(const AString & column) const
{
	if (!private_->database || !private_->database->isOpen()) {
		printSqlError(__FILE__, __FUNCTION__, __LINE__,
			"Database is not opened.");
		return SqlVariant(nullptr);
	}

	if (!private_->parsedQuery) {
		private_->nextOnError = true;
		printSqlError(
			__FILE__, __FUNCTION__, __LINE__,
			"Couldn't request results. Probably bind values not added?\n");
		return SqlVariant(nullptr);
	}

	for (size_t i = 0; i < private_->parsedQuery->columns.size(); ++i) {
		if (column == private_->parsedQuery->columns[i].name) {
			if (private_->executedPrepared) {
				return SqlVariant(private_->results[i].buffer);
			}
			return SqlVariant(private_->lastRow[i], false, true);
		}
	}

	auto message("Couldn't request value of column '" + column + "', ");
	message += "the only selectable values of columns are: \n";
	const auto columnListSize = private_->parsedQuery->columns.size();

	for (size_t i = 0; i < columnListSize; ++i) {
		message += private_->parsedQuery->columns[i].name + (i == columnListSize - 1 ? "" : ", ");
	}

	printSqlError(__FILE__, __FUNCTION__, __LINE__, message.c_str());
	return SqlVariant(nullptr);
}

/**
 * \brief Returns record count.
 * \return record count
 */
uint64 SqlQuery::getRecordCount() const
{
	return private_->recordCount;
}

/**
 * \brief Returns field count.
 * \return field count
 */
uint64 SqlQuery::getFieldCount() const
{
	return private_->parsedQuery ? private_->parsedQuery->columns.size() : 0;
}

/**
 * \brief Clears some vars to get prepared for the next query execution.
 */
void SqlQuery::clear() const
{
	private_->parameters.clear();
	private_->parameterValues.clear();
	private_->query.clear();
	private_->isSelectCommand = false;

	private_->nextOnError = false;
	private_->recordCount = 0;

	if (private_->lastResult) {
		mysql_free_result(private_->lastResult);
		private_->lastResult = nullptr;
	}

	if (private_->statement) {
		mysql_stmt_free_result(private_->statement.get());
		mysql_stmt_close(private_->statement.get());
		private_->statement = nullptr;
	}

	if (private_->parsedQuery) {
		const auto columnCount = private_->parsedQuery->columns.size();
#pragma warning(disable : 6305)
		for (uint64 i = 0; i < columnCount && (private_->results + i * sizeof(MYSQL_BIND)) != nullptr; ++i) {
			delete[] static_cast<char*>(private_->results[i].buffer);
		}
#pragma warning(default : 6305)
		private_->parsedQuery = nullptr;
	}
	DELETE_ARR(private_->results);
}

/**
 * \brief Sets current database pointer to database with connectionName equals to passed param connectionName.
 * \param connectionName connection name
 */
void SqlQuery::setDatabase(const AString & connectionName) const
{
	private_->database = SqlDatabase::database(connectionName);
}

void SqlQuery::printSqlError()
{
	printSqlError("", "", 0, "");
}

/**
 * \brief Adds value bind with type, buffer, isUnsigned and bufferLength passed by params.
 * \param type mysql type
 * \param buffer void array
 * \param isUnsigned whether is unsigned or not
 * \param bufferLength length of buffer
 */
void SqlQuery::addBindValue(const int type,
	void* buffer,
	const char isUnsigned,
	const uint bufferLength) const
{
	MYSQL_BIND bind;
	ZeroMemory(&bind, sizeof(MYSQL_BIND));
	bind.buffer = buffer;
	bind.buffer_type = static_cast<enum_field_types>(type);
	bind.is_unsigned = static_cast<my_bool>(isUnsigned);
	bind.buffer_length = bufferLength;
	private_->parameters.append(bind);
}

/**
 * \brief Parses query to determine each column type etc.
 * \return shared_ptr to sqltable
 */
std::shared_ptr<SqlTable> SqlQuery::parseQuery() const
{
	auto currentTable = std::make_shared<SqlTable>();
	auto copyQuery = AString(private_->query);
	copyQuery.replaceAll(",", " ");
	copyQuery.replaceAll("  ", " ");
	auto querySplitted = copyQuery.split(' ');

	auto tableColumnListContains = [currentTable](const AString & columnName) {
		for (auto& column : currentTable->columns) {
			if (column.name == columnName) {
				return true;
			}
		}
		return false;
	};

	auto allExpected = false;
	for (size_t i = 0; i < querySplitted.size(); ++i) {
		const auto command = AString(querySplitted[i]).toLower();
		if (i == 0) {
			private_->isSelectCommand = command == "select";
		}
		if (i == 0 && command != "select" && command != "update") {
			return currentTable;
		}
		if (querySplitted[i] == "*") {
			allExpected = true;
		}
		else if (command == "from") {
			if (allExpected) {
				if (i < querySplitted.size() - 1) {
					currentTable->name = querySplitted[i + 1];
				}
				else {
					return currentTable;
				}
				for (auto& table : private_->database->getTables()) {
					if (table->name == currentTable->name) {
						for (size_t k = 0; k < table->columns.size(); ++k) {
							if (!tableColumnListContains(table->columns[k].name)) {
								SqlColumn column;
								column.name = table->columns[k].name;
								column.type = table->columns[k].type;
								column.length = table->columns[k].length;
								currentTable->columns.append(column);
							}
							continue;
						}
					}
				}
				return currentTable;
			}
			const auto maxIndex = querySplitted.size() - 1;
			if (i < querySplitted.size() - 1) {
				currentTable->name = querySplitted[i + 1];
			}
		}
		else if (command != "select" && command != "update") {
			if (i < querySplitted.size() - 1 && command == "count"
				&& AString(querySplitted[i + 1]).toLower() == "(*)"
				|| command.startsWith("count(")) {
				if (!tableColumnListContains(querySplitted[i])) {
					SqlColumn column;
					column.name = "count";
					column.length = sizeof(int);
					column.type = MYSQL_TYPE_LONG;
					currentTable->columns.append(column);
				}
				break;
			}
			else {
				for (auto& table : private_->database->getTables()) {
					for (size_t k = 0; k < table->columns.size(); ++k) {
						if (table->columns[k].name == querySplitted[i]) {
							if (!tableColumnListContains(table->columns[k].name)) {
								SqlColumn column;
								column.name = table->columns[k].name;
								column.type = table->columns[k].type;
								column.length = table->columns[k].length;
								currentTable->columns.append(column);
							}
							continue;
						}
					}
				}
			}
		}
	}
	return currentTable;
}

void SqlQuery::countRows(const AString & query) const
{
	SqlQuery countQuery(private_->database->getConnectionName());
	countQuery.private_->countRows = false;

	const auto querySplitted = query.split(' ');
	const auto maxIndex = querySplitted.size() - 1;
	AString tableName;

	for (size_t i = 0; i < maxIndex; ++i) {
		if (AString(querySplitted[i]).toLower() == "from") {
			tableName = querySplitted[i + 1];
		}
	}

	if (!tableName.isEmpty()) {
		countQuery.prepare("SELECT COUNT(*) FROM " + tableName);
		if (countQuery.exec() && countQuery.next()) {
			private_->recordCount = countQuery.value("count").toUInt();
		}
	}
}

/**
 * \brief Prints sql error with source file, function, line and reason passed by params.
 * \param file source file
 * \param function function in source file
 * \param line line in source file
 * \param reason reason to fail
 */
void SqlQuery::printSqlError(const char* file,
	const char* function,
	const int line,
	const char* reason) const
{
	AString errorCode;
	AString errorString;
	if (private_->executedPrepared) {
		errorCode = AString::toString(private_->statement->last_errno);
		errorString = private_->statement->last_error;
	}
	else {
		errorCode = AString::toString(mysql_errno(private_->database->getMySql()));
		errorString = mysql_error(private_->database->getMySql());
	}

	Logger::error("SqlQuery error, code: " + errorCode);
	Logger::error("Error message: " + errorString);
	Logger::error("File: " + AString(file));
	Logger::error("Function: " + AString(function));
	Logger::error("Line: " + AString::toString(line));
	Logger::error("Reason: " + AString(reason ? reason : "NULL"));
}
