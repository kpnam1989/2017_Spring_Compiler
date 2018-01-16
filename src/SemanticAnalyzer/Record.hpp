
#ifndef RECORD_HPP
#define RECORD_HPP

#include <fstream>

class Record {
private:

public:
	int functionIndex = 0; // a helper attribute used when evaluating function
	int scopeLevel = 0;
	std::string type;
	std::string dimension = "0";
	std::string value;
	std::vector<std::string> parameters;
	std::vector<std::string> parameterTypes;
	std::vector<std::string> parameterDimensions;
	std::string returnType;
	std::string tableType;

	// DeclaredType to help with type checking
	std::string NamedType;

	Record(int scopeLevel) {
		this->scopeLevel = scopeLevel;
	}

	Record(){}

	double getValue(){
		if (value == ""){
			return(0);
		} else {
			return(std::stoi(value));
		}

	}
	void toString() {
		std::cout << "Table: " << tableType << std::endl;
		std::cout << "Scope: " << scopeLevel << std::endl;
		std::cout << "Type: " << type << std::endl;
		std::cout << "Dimension: " << dimension << std::endl;
		std::cout << "Parameters: ";
		for (std::vector<std::string>::iterator it = parameters.begin();
				it != parameters.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "Parameter types: ";
		for (std::vector<std::string>::iterator it = parameterTypes.begin();
				it != parameterTypes.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "Parameter dimensions: ";
		for (std::vector<std::string>::iterator it =
				parameterDimensions.begin(); it != parameterDimensions.end();
				++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "Return Type: " << returnType << std::endl;
		std::cout << "Value: " << value << std::endl;

	}

	void WriteToFile(std::ostream &fileStream) {
		fileStream << "Table: " << tableType << std::endl;
		fileStream << "Scope: " << scopeLevel << std::endl;
		fileStream << "Type: " << type << std::endl;
		fileStream << "Named type: " << NamedType << std::endl;
		fileStream << "Dimension: " << dimension << std::endl;
		fileStream << "Parameters: ";
		for (std::vector<std::string>::iterator it = parameters.begin();
				it != parameters.end(); ++it) {
			fileStream << "[" << *it << "]" << " ";
		}
		fileStream << std::endl;

		fileStream << "Parameter types: ";
		for (std::vector<std::string>::iterator it = parameterTypes.begin();
				it != parameterTypes.end(); ++it) {
			fileStream << "[" << *it << "]" << " ";
		}
		fileStream << std::endl;

		fileStream << "Parameter dimensions: ";
		for (std::vector<std::string>::iterator it =
				parameterDimensions.begin(); it != parameterDimensions.end();
				++it) {
			fileStream << "[" << *it << "]" << " ";
		}

		fileStream << std::endl;

		fileStream << "Return Type: " << returnType << std::endl;
		fileStream << "Value: " << value << std::endl;
	}

};

#endif
