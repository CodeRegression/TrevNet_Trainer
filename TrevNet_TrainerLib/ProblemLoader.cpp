//--------------------------------------------------
// Implementation of class ProblemLoader
//
// @author: Wild Boar
//
// @date: 2022-12-28
//--------------------------------------------------

#include "ProblemLoader.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param problemCode The code of the problem we are processing
 * @param dataFile The path to the associated data file
 */
ProblemLoader::ProblemLoader(const string& problemCode, const string& dataFile) : _code(problemCode), _file(dataFile)
{
	_id = -1; _name = string(); _description = string(); _fileHash = "unknown"; _reader = nullptr;
}

/**
 * @brief Main Terminator
 */
ProblemLoader::~ProblemLoader()
{
	if (_reader != nullptr) delete _reader;
}

//--------------------------------------------------
// Loader
//--------------------------------------------------

/**
 * @brief Load problem details
 * @param codeDash Link to the code data database
 */
void ProblemLoader::Load(CodeDash * codeDash)
{
	// Get the problem details
	auto details = codeDash->GetProblemDetails(_code);

	// Break the details into parts
	auto parts = vector<string>(); NVLib::StringUtils::Split(details, ',', parts);
	_id = NVLib::StringUtils::String2Int(parts[0]);
	_name = parts[1]; _description = parts[2]; _fileHash = parts[4];

	// Check to see if the file exists
	if (!NVLib::FileUtils::Exists(_file)) throw runtime_error("Unable to find the provided data file");
	auto actualHash = NVLib::FileUtils::GetFileHash(_file);
	if (actualHash != _fileHash) throw runtime_error("The data file does not appear to be valid - please download the proper one");

	// Load the data file
	_reader = new NVLib::ARFFReader(_file);
	_data = _reader->ReadAll();
}