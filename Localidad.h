#pragma once
#include <string>

class Localidad {
		public:
			Localidad();
			Localidad(int codigoPostal, std::string localidad, std::string partido);

			int getCodigoPostal();
			std::string getLocalidad();
			std::string getPartido();

			void setLocalidad(std::string localidad);
			void setPartido(std::string partido);
			void setCodigoPostal(int codigoPostal);

		private:
			char _localidad[70];
			char _partido[50];
			int _codigoPostal;
};
