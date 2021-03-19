#ifndef ALUMNO_H
#define ALUMNO_H

	class Alumno {
		std::string nombre;
		int padron;
	public:
		Alumno();
		Alumno(std::string& nombre, int padron);
		Alumno(const Alumno& other);
		const Alumno& operator=(const Alumno& other);
		bool operator<(const Alumno& other) const;
		bool operator==(const Alumno& other) const;
		friend std::ostream& operator<<(std::ostream& o,const Alumno& alumno);
		operator int() const;
		~Alumno();
	};

#endif