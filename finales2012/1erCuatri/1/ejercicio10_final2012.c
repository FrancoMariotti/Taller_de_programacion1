/*
	Describa con exactitud las siguientes declaraciones/definiciones globales:
*/

//declaracion arreglo de enteros short cuya definicion se encuentra en otro archivo.
extern 	short int S[2];

/* declaracion de un arreglo de punteros a double el cual es unicamente visible 
 * dentro del archivo donde se lo declaro.
 */
static 	double (*I)[3];

/* definicion de una funcion resta que recibe un numero a de tipo flotante un numero b de tipo doble y 
 * retorna un numero entero de tipo int que representa la resta de a y b. Esta solo es visible dentro 
 * del archivo donde se la definio.
 */
static 	int resta(float a, double b) {return a-b;}