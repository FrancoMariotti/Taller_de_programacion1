//-----------------------------------------------------------------------------
// TALLER DE PROGRAMACION I
//
// Temas a ejemplificar: constructor de copia, sobrecarga de operadores
//-----------------------------------------------------------------------------
#ifndef _COMPLEJO_H_
#define _COMPLEJO_H_

#include <ostream>
//-----------------------------------------------------------------------------
// Clase cComplejo: El objetivo de esta clase es el manejo de numeros complejos
//-----------------------------------------------------------------------------
class cComplejo {
  private:
  int real, imaginario;
  // la sobrecarga del operador << no es realizada mediante metodo de
  // clase; se declara la funcion como friend (amiga) de la clase de
  // forma tal que la misma pueda acceder a la parte no-publica de la clase
  friend std::ostream &operator<<( std::ostream &stream, const cComplejo &complejo );
  // funcion privada utilizada internamente por los metodos publicos
  void set( int real, int imaginario );
  public:
  // constructor de copia y constructor con parametros con valores por
  // default; permiten instancias de los tipos 'cComplejo cmpx2( cmpx1 )',
  // 'cComprejo cmpx', 'cComplejo cmpx( 20 )', 'cComplejo cmpx( 20, 10 )'
  cComplejo( int real = 0, int imaginario = 0 );
  cComplejo( const cComplejo &parametro );
  // sobrecarga del operador = entre dos objetos del tipo cComplejo
  const cComplejo &operator=( const cComplejo &origen );
  // dos sobrecargas del operador +, para dos tipos de datos distintos
  // a la derecha del operador
  cComplejo operator+( const cComplejo &param ) const;
  cComplejo operator+( int param ) const;
  // dos sobrecargas del operador +=, para dos tipos de datos distintos
  // a la derecha del operador
  const cComplejo &operator+=( const cComplejo &param );
  const cComplejo &operator+=( int param );
  // dos sobrecargas del operador ++
  // difieren en que una es pre-incremento y la otra post-incremento
  cComplejo &operator++();
  cComplejo operator++( int );
  // sobrecarga de operadores de comparacion. Notar que los dos primeros
  // son la base de los siguientes (ver codigo abajo)
  bool operator==( const cComplejo &param ) const;
  bool operator<( const cComplejo &param ) const;
  bool operator!=( const cComplejo &param ) const;
  bool operator>( const cComplejo &param ) const;
  bool operator>=( const cComplejo &param ) const;
  bool operator<=( const cComplejo &param ) const;
  // operador de conversion de tipo a int
 operator int() const;
};
#endif // _COMPLEJO_H_