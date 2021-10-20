#include "GLCheck.h"
#include <glad/glad.h>
#include <iostream>

void asx::GLCheckError(std::string_view expression, std::source_location x)
{
	auto errorCode = glGetError();

	if(errorCode != GL_NO_ERROR)
	{
		std::string error = "Unknown error";
		std::string description = "No description";

		switch(errorCode)
		{
			case GL_NO_ERROR:
				error = "GL_NO_ERROR";
				description = "No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
				break;

			case GL_INVALID_ENUM:
				error = "GL_INVALID_ENUM";
				description = "An unacceptable value is specified for an enumerated argument.";
				break;

			case GL_INVALID_VALUE:
				error = "GL_INVALID_VALUE";
				description = "A numeric argument is out of range.";
				break;

			case GL_INVALID_OPERATION:
				error = "GL_INVALID_OPERATION";
				description = "The specified operation is not allowed in the current state.";
				break;

			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error = "GL_INVALID_FRAMEBUFFER_OPERATION";
				description = "The framebuffer object is not complete.";
				break;

			case GL_OUT_OF_MEMORY:
				error = "GL_OUT_OF_MEMORY";
				description = "There is not enough memory left to execute the command.";
				break;

			case GL_STACK_UNDERFLOW:
				error = "GL_STACK_UNDERFLOW";
				description = "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
				break;

			case GL_STACK_OVERFLOW:
				error = "GL_STACK_OVERFLOW";
				description = "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
				break;
		}

		std::cerr << "An internal OpenGL call failed in " << x.file_name() << "(" << x.line() << ")\n"
				  << "Expression:\n\t" << expression << "\n"
				  << "Error description:\n\t" << error << "\n"
				  << "\t" << description << "\n"
				  << std::endl;
	}
}
