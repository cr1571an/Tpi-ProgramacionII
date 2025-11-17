#pragma once
#include <string>

class Localidad {
	public:
		Localidad();
		Localidad(int idLocalidad,int codigoPostal, std::string localidad, std::string partido);

		int getCodigoPostal();
		int getIDLocalidad();
		std::string getLocalidad();
		std::string getPartido();
		bool operator==(Localidad otra);

		void setIDLocalidad(int idLocalidad);
		void setLocalidad(std::string localidad);
		void setPartido(std::string partido);
		void setCodigoPostal(int codigoPostal);

	private:
		int _idLocalidad, _codigoPostal;
		char _localidad[70], _partido[50];
};