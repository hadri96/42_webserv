#include "ConfigInterpreterContext.hpp"

#include "ToVector.hpp"
#include <vector>
#include <string>



ConfigInterpreterContext::ConfigInterpreterContext(void)
{}

ConfigInterpreterContext::ConfigInterpreterContext(const ConfigInterpreterContext& other)
{}

ConfigInterpreterContext::ConfigInterpreterContext(
	const char* context[], 
	const char* validBlocks[],
	const char* validDirectives[],
	void (*directivesHandlers[])(ConfigParserNode*)
) :
	context_(toVector(context)),
	validBlocks_(toVector(validBlocks)),
	validDirectives_(toVector(validDirectives)),
	directivesHandlers_(toVector(directivesHandlers))
{}

ConfigInterpreterContext::~ConfigInterpreterContext(void)
{}

ConfigInterpreterContext&	ConfigInterpreterContext::operator=(const ConfigInterpreterContext& rhs)
{}

