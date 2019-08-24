#include "file.h"

#include <cstdio>
#include <sstream>

#include "console.h"
#include "dir.h"
#include "logger.h"

File::File() :
	openModeFlags_(OpenMode::NotOpen),
	atEnd_(false)
{}

File::File(const File& file) :
	filepath_(file.filepath_),
	openModeFlags_(file.openModeFlags_)
{
	if (file.isOpen()) {
		open(openModeFlags_);
	}
}

File::File(const AString& filepath) noexcept :
	File()
{
	setFilepath(filepath);
}

File::~File()
{
	if (isOpen()) {
		close();
	}
}

bool File::create(const bool recursively) const
{
	auto dir = Dir(getDirectory());

	auto result = true;
	if (!dir.exists()) {
		result = dir.create(recursively);
	}

	std::ofstream outfile(filepath_);
	outfile << "";
	outfile.close();
	return result && outfile.good();
}

bool File::create(const AString& filepath, const bool recursively)
{
	return File(filepath).create(recursively);
}

bool File::erase() const
{
	return !::remove(filepath_.toCString());
}

bool File::erase(const AString& filepath)
{
	return File(filepath).erase();
}

bool File::exists() const
{
	std::ifstream infile(filepath_);
	return infile.good();
}

bool File::exists(const AString& filepath)
{
	return File(filepath).exists();
}


AString File::getDirectory() const
{
	if (filepath_.count("/") == 0 && filepath_.count("\\") == 0) {
		return AString(Dir::getDir(Directory::CurrentApplication));
	}

	// TODO: Return absolute directory from relative
	auto lastIndexOfSlash = filepath_.lastIndexOf('/');

	if (lastIndexOfSlash == static_cast<size_t>(-1)) {
		return AString();
	}

	auto copy = filepath_;
	copy.erase(static_cast<size_t>(lastIndexOfSlash), copy.size() - 1);
	return copy;
}

AString File::getFilename() const
{
	auto lastIndexOfSlash = filepath_.lastIndexOf('/');
	if (lastIndexOfSlash == static_cast<size_t>(-1)) {
		lastIndexOfSlash = filepath_.lastIndexOf('\\');
		if (lastIndexOfSlash == static_cast<size_t>(-1)) {
			return filepath_;
		}
	}

	auto copy = filepath_;
	copy.erase(0, lastIndexOfSlash + 1);
	return copy;
}

AString File::getFilepath() const
{
	return filepath_;
}

void File::setFilepath(const AString& filepath)
{
	filepath_ = filepath;
	filepath_.replaceAll("\\", "/");
}

bool File::isOpen() const
{
	return fstream_.is_open();
}

bool File::open(int openModeFlags)
{
	auto result = true;
	if (!exists()) {
		result = create();
	}
	if (filepath_.isEmpty()) {
		return false;
	}
	openModeFlags_ = openModeFlags;
	fstream_.open(filepath_.toCString(), static_cast<std::ios_base::openmode>(openModeFlags_));
	atEnd_ = false;
	return result && isOpen();
}

void File::close()
{
	fstream_.close();
}
void File::operator=(const File& file)
{
	filepath_ = file.filepath_;
	openModeFlags_ = file.openModeFlags_;

	if (file.isOpen()) {
		open(openModeFlags_);
	}
}

std::fstream& File::operator<<(const AString& string)
{
	if (!printFileOpen() || !printFlagWriteOnly()) {
		return fstream_;
	}
	if ((openModeFlags_ & OpenMode::NewOnly) && exists()) {
		Logger::error("Failed to write to file, Flag NewOnly was set.");
		return fstream_;
	}
	if ((openModeFlags_ & OpenMode::ExistingOnly) && !exists()) {
		Logger::error("Failed to write to file, Flag NewOnly was set.");
		return fstream_;
	}

	fstream_ << string;
	fstream_.flush();
	return fstream_;
}

void File::append(const AString& string)
{
	if (!printFileOpen() || !printFlagWriteOnly()) {
		return;
	}

	if (!(openModeFlags_ & OpenMode::Append)) {
		Logger::error("Failed writing to file '" + filepath_ +
			"'. Flag Append was not set.");
		return;
	}

	fstream_ << string;
	fstream_.flush();
}

AString File::readAllText()
{
	if (isOpen()) {
		close();
	}
	open(OpenMode::ReadOnly);
	const auto result = AString(std::istreambuf_iterator<char>(fstream_), std::istreambuf_iterator<char>());
	close();
	return result;
}

void File::writeAllText(const AString& text)
{
	if (isOpen()) {
		close();
	}
	if (!open(OpenMode::WriteOnly)) {
		Logger::error("Couldn't reopen file '" + filepath_ + "' to get bytes.");
		return;
	}
	fstream_ << text;
	fstream_.flush();
}

ByteArray File::readAllBytes()
{
	if (isOpen()) {
		close();
	}
	if (!open(OpenMode::ReadOnly | OpenMode::Binary | OpenMode::AtTheEnd)) {
		Logger::error("Couldn't reopen file '" + filepath_ + "' to get bytes.");
		return ByteArray();
	}
	const size_t pos = static_cast<size_t>(fstream_.tellg());

	std::shared_ptr<char> buffer = std::shared_ptr<char>(new char[pos], [](const char* buffer) { delete[] buffer; });
	fstream_.seekg(0, std::ios::beg);
	fstream_.read(buffer.get(), pos);
	close();

	return ByteArray(buffer.get(), pos);
}

void File::writeAllBytes(const ByteArray& bytes)
{
	if (isOpen()) {
		close();
	}
	if (!open(OpenMode::WriteOnly | OpenMode::Binary)) {
		Logger::error("Couldn't reopen file '" + filepath_ + "' to get bytes.");
		return;
	}
	fstream_.write(bytes.data(), bytes.size());
	fstream_.close();
}

AString File::readLine()
{
	if (!printFileOpen() || !printFlagReadOnly()) {
		return "empty";
	}

	AString temp;
	std::getline(fstream_, temp);
	atEnd_ = fstream_.peek() == EOF;
	return temp;
}

bool File::atEnd() const
{
	return isOpen() && atEnd_;
}

bool File::printFileOpen() const
{
	if (!isOpen()) {
		Logger::error("Couldn't write to file '" + filepath_ +
			"'. File stream is not opened.");
		return false;
	}
	return true;
}

bool File::printFlagReadOnly() const
{
	if (!(openModeFlags_ & OpenMode::ReadOnly)) {
		Logger::error("Failed writing to file '" + filepath_ +
			"'. Flag ReadOnly was not set.");
		return false;
	}
	return true;
}

bool File::printFlagWriteOnly() const
{
	if (!(openModeFlags_ & OpenMode::WriteOnly)) {
		Logger::error("Failed writing to file '" + filepath_ +
			"'. Flag WriteOnly was not set.");
		return false;
	}
	return true;
}
