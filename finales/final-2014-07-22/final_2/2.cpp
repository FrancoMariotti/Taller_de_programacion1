#ifndef ALUMNO_H
#define ALUMNO_H

	class Alumno {
	public:
		Alumno();
		Alumno(const Alumno& other);
		Alumno(int padron);
		const Alumno& operator=(const Alumno& other);
		bool operator<(const Alumno& other) const;
		bool operator==(const Alumno& other) const;
		friend std::ostream& operator<<(std::ostream& o,const Alumno& alumno);
		operator int() const;
		~Alumno();
	};

#endif