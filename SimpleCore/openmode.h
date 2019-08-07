#ifndef OPENMODE_H
#define OPENMODE_H

/**
 * Provides flags for opening a file.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
enum OpenMode {
	NotOpen = 0x0,
	ReadOnly = 0x1,
	WriteOnly = 0x2,
	ReadWrite = ReadOnly | WriteOnly,
	AtTheEnd = 0x4,
	Append = 0x8,
	Truncate = 0x10,
	Binary = 0x20,
	NewOnly = 0x40,
	ExistingOnly = 0x80
};

#endif // OPENMODE_H
