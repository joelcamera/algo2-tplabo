#ifndef PLANIFICADOR_RR_H_
#define PLANIFICADOR_RR_H_

#include <iostream>
#include <cassert>
using namespace std;

/**
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class PlanificadorRR {

  public:

	/**
	 * Crea un nuevo planificador de tipo Round Robin.
	 */	
	PlanificadorRR();

	/**
	 * Una vez copiado, ambos planificadores deben ser independientes, 
	 * es decir, por ejemplo, que cuando se borra un proceso en uno
	 * no debe borrarse en el otro.
	 */	
	PlanificadorRR(const PlanificadorRR<T>& otro);

	/**
	 * Acordarse de liberar toda la memoria!
	 */	 
	~PlanificadorRR();

	/**
	 * Agrega un proceso al planificador. El mismo debe ubicarse,
	 * dentro del orden de ejecución, inmediatamente antes del que está
	 * siendo ejecutado actualmente. Si no hubiese ningún proceso en ejecución,
	 * la posición es arbitraria y el proceso pasa a ser ejecutado automáticamente.
	 * PRE: El proceso no está siendo planificado por el planificador.
	 */
	void agregarProceso(const T& elem);

	/**
	 * Elimina un proceso del planificador. Si el proceso eliminado
	 * está actualmente en ejecución, automáticamente pasa a ejecutarse
	 * el siguiente (si es que existe).
	 * PRE: El proceso está siendo planificado por el planificador.
	 */
	void eliminarProceso(const T& elem);

	/**
	 * Devuelve el proceso que está actualmente en ejecución.
	 * PRE: Hay al menos un proceso activo en el planificador.
	 */
	const T& procesoEjecutado() const;

	/**
	 * Procede a ejecutar el siguiente proceso activo,
	 * respetando el orden de planificación.
	 * PRE: Hay al menos un proceso activo en el planificador.
	 */
	void ejecutarSiguienteProceso();

	/**
	 * Pausa un proceso por tiempo indefinido. Este proceso pasa
	 * a estar inactivo y no debe ser ejecutado por el planificador.
	 * Si el proceso pausado está actualmente en ejecución, automáticamente
	 * pasa a ejecutarse el siguiente (si es que existe).
	 * PRE: El proceso está siendo planificado por el planificador.
	 * PRE: El proceso está activo.
	 */
	void pausarProceso(const T& elem);

	/**
	 * Reanuda un proceso previamente pausado. Este proceso pasa a estar
	 * nuevamente activo dentro del planificador. Si no había ningún proceso
	 * en ejecución, el proceso pasa a ser ejecutado automáticamente.
	 * PRE: El proceso está siendo planificado por el planificador.
	 * PRE: El proceso está inactivo.
	 */
	void reanudarProceso(const T& elem);

	/**
	 * Detiene la ejecución de todos los procesos en el planificador
	 * para atender una interrupción del sistema.
	 * PRE: El planificador no está detenido.
	 */
	void detener();

	/**
	 * Reanuda la ejecución de los procesos (activos) en el planificador
	 * luego de atender una interrupción del sistema.
	 * PRE: El planificador está detenido.
	 */
	void reanudar();

	/**
	 * Informa si el planificador está detenido por el sistema operativo.
	 */
	bool detenido() const;

	/**
	 * Informa si un cierto proceso está siendo planificado por el planificador.
	 */
	bool esPlanificado(const T& elem) const;

	/**
	 * Informa si un cierto proceso está activo en el planificador.
	 * PRE: El proceso está siendo planificado por el planificador.
	 */
	bool estaActivo(const T& elem) const;

	/**
	 * Informa si existen procesos planificados.
	 */
	bool hayProcesos() const;

	/**
	 * Informa si existen procesos activos.
	 */
	bool hayProcesosActivos() const;

	/**
	 * Devuelve la cantidad de procesos planificados.
	 */
	int cantidadDeProcesos() const;

	/**
	 * Devuelve la cantidad de procesos planificados y activos.
	 */
	int cantidadDeProcesosActivos() const;

	/**
	 * Devuelve true si ambos planificadores son iguales.
	 */
	bool operator==(const PlanificadorRR<T>& otro) const;

	/**
	 * Debe mostrar los procesos planificados por el ostream (y retornar el mismo).
	 * Los procesos deben aparecer en el mismo orden en el que son ejecutados
	 * por el planificador. Como la lista es circular, se decidió que el primer
	 * proceso que se muestra debe ser el que está siendo ejecutado en ese momento.
	 * En el caso particular donde exista al menos un proceso planificado,
	 * pero estén todos pausados, se puede comenzar por cualquier proceso.
	 * Un proceso inactivo debe ser identificado con el sufijo ' (i)'
	 * y el proceso que está siendo ejecutado, de existir, debe ser identificado
	 * con el sufijo '*'.
	 * PlanificadorRR vacio: []
	 * PlanificadorRR con 1 elemento activo: [p0*]
	 * PlanificadorRR con 2 elementos inactivos: [p0 (i), p1 (i)]
	 * PlanificadorRR con 3 elementos (p0 inactivo, p2 siendo ejecutado: [p2*, p0 (i), p1]
	 *
	 * OJO: con pX (p0, p1, p2) nos referimos a lo que devuelve el operador <<
	 * para cada proceso, es decir, cómo cada proceso decide mostrarse en el sistema.
	 * El sufijo 'X' indica el orden relativo de cada proceso en el planificador.
	 */
	ostream& mostrarPlanificadorRR(ostream& os) const;

  private:
  
	/**
	 * No se puede modificar esta funcion.
	 */
	PlanificadorRR<T>& operator=(const PlanificadorRR<T>& otra) {
		assert(false);
		return *this;
	}

	/**
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {

		Nodo(const T& e) : elem(e),estaPausado(false),sig(NULL),ant(NULL){
		}

		Nodo(){}

		T elem;
		bool estaPausado;
		Nodo* sig;
		Nodo* ant;
	};


	
	/******* ESTRUCTURA **********/
	Nodo* actual;
	bool planDetenido;
	int cantProcesos;
	int cantProActivos;



	/******* FUNCIONES AUXILIARES ************/
	typename PlanificadorRR<T>::Nodo* buscoSigActivo(Nodo* buscanodo);
	typename PlanificadorRR<T>::Nodo* buscaNodoElem(const T& elem)const;
	void setCantProActivos(short i);

};

template<class T>
ostream& operator<<(ostream& out, const PlanificadorRR<T>& a) {
	return a.mostrarPlanificadorRR(out);
}




/*************** FUNCIONES PLANIFICADOR_RR<T> *******************/




/**
 * Crea un nuevo planificador de tipo Round Robin.
 */	
template<typename T>
PlanificadorRR<T>::PlanificadorRR(){
	this->actual = NULL;
	this->planDetenido = false;
	this->cantProcesos = 0;
	this->cantProActivos = 0;
}

/**
 * Una vez copiado, ambos planificadores deben ser independientes, 
 * es decir, por ejemplo, que cuando se borra un proceso en uno
 * no debe borrarse en el otro.
 */	
template<typename T>
PlanificadorRR<T>::PlanificadorRR(const PlanificadorRR<T>& otro){
	this->actual = NULL;
	this->planDetenido = false;
	this->cantProcesos = 0;
	this->cantProActivos = 0;

	Nodo* buscanodo = otro.actual;
	int i = otro.cantProcesos;
	
	while(i > 0){
		this->agregarProceso(buscanodo->elem);

		if(buscanodo->estaPausado){
			this->pausarProceso(buscanodo->elem);
		}

		buscanodo = buscanodo->sig;
		i--;
	}
}

/**
 * Acordarse de liberar toda la memoria!
 */
template<typename T>
PlanificadorRR<T>::~PlanificadorRR(){
	if(this->cantProcesos == 1){
		Nodo* nodoborrar = this->actual;
		this->actual = NULL;

		delete nodoborrar;
	
	} else if (this->cantProcesos > 1){
		Nodo* nodoborrar;

		while(this->cantProcesos >= 1){
			nodoborrar = this->actual;

			if(this->cantProcesos == 1){
				this->actual = NULL;
			} else {
				this->actual = this->actual->sig;
			}

			delete nodoborrar;
			this->cantProcesos--;
		}
	}
}

/**
 * Agrega un proceso al planificador. El mismo debe ubicarse,
 * dentro del orden de ejecución, inmediatamente antes del que está
 * siendo ejecutado actualmente. Si no hubiese ningún proceso en ejecución,
 * la posición es arbitraria y el proceso pasa a ser ejecutado automáticamente.
 * PRE: El proceso no está siendo planificado por el planificador.
 */
template<typename T>
void PlanificadorRR<T>::agregarProceso(const T& elem){
	if( !detenido() && !esPlanificado(elem) ){
		if(this->cantProcesos == 0 && this->actual == NULL){
			this->actual = new Nodo(elem);
			this->actual->sig = this->actual;
			this->actual->ant = this->actual;
		
		} else {
			Nodo* nuevo = new Nodo(elem);
			Nodo* anterior = this->actual->ant;
	
			//conecto el nodo anterior con el nuevo
			nuevo->ant = anterior;
			anterior->sig = nuevo;
	
			//conecto el nodo actual con el nuevo
			this->actual->ant = nuevo;
			nuevo->sig = this->actual;
		}
		this->cantProcesos++;
		this->cantProActivos++;
	}
}

/**
 * Elimina un proceso del planificador. Si el proceso eliminado
 * está actualmente en ejecución, automáticamente pasa a ejecutarse
 * el siguiente (si es que existe).
 * PRE: El proceso está siendo planificado por el planificador.
 */
template<typename T>
void PlanificadorRR<T>::eliminarProceso(const T& elem){
	if ( !detenido() && esPlanificado(elem) ){
		Nodo* paraborrar = this->actual;

		if(this->cantProcesos != 1){
		
			while( !(paraborrar->elem == elem) ) {
				paraborrar = paraborrar->sig;
			}
		
			if(this->actual->elem == elem) {
				//si estoy borrando el actual y no hay mas procesos
				//activos, pongo el siguiente y listo
				if(this->cantProActivos > 1 && !this->actual->estaPausado){
					this->actual = buscoSigActivo(this->actual->sig);
				} else {
					this->actual = this->actual->sig;
				}

			}

			//aca tengo el nodo para borrar
			//conecto los nodos de al rededor
			Nodo* anterior = paraborrar->ant;
			Nodo* siguiente = paraborrar->sig;
			anterior->sig = siguiente;
			siguiente->ant = anterior;

		} else {
			this->actual = NULL;
		}
		
		this->cantProcesos--;
		if ( !paraborrar->estaPausado ) this->cantProActivos--;

		delete paraborrar;	
	}
}

/**
 * Devuelve el proceso que está actualmente en ejecución.
 * PRE: Hay al menos un proceso activo en el planificador.
 */
template<typename T>
const T& PlanificadorRR<T>::procesoEjecutado() const{
	if (this->actual != NULL && !this->actual->estaPausado){
		return this->actual->elem;
	}

	//devuelvo basura para que no tire mas el warning
	//por requiere lo puedo hacer
	const T& t = 0;
	return t;
}

/**
 * Procede a ejecutar el siguiente proceso activo,
 * respetando el orden de planificación.
 * PRE: Hay al menos un proceso activo en el planificador.
 */
template<typename T>
void PlanificadorRR<T>::ejecutarSiguienteProceso(){
	if (!detenido() && this->cantProcesos > 1 && this->cantProActivos > 1){
		this->actual = this->actual->sig;
		
		while( this->actual->estaPausado ){
			this->actual = this->actual->sig;
		}
	}
}

/**
 * Pausa un proceso por tiempo indefinido. Este proceso pasa
 * a estar inactivo y no debe ser ejecutado por el planificador.
 * Si el proceso pausado está actualmente en ejecución, automáticamente
 * pasa a ejecutarse el siguiente (si es que existe).
 * PRE: El proceso está siendo planificado por el planificador.
 * PRE: El proceso está activo.
 */
template<typename T>
void PlanificadorRR<T>::pausarProceso(const T& elem){
	
	if(!detenido() && esPlanificado(elem) && estaActivo(elem) ){
		Nodo* buscanodo = buscaNodoElem(elem);
		
		buscanodo->estaPausado = true;
		setCantProActivos(-1);

		if(this->actual->elem == elem && this->cantProActivos > 0){
			this->actual = buscoSigActivo(this->actual);
		}
	}
}

/**
 * Reanuda un proceso previamente pausado. Este proceso pasa a estar
 * nuevamente activo dentro del planificador. Si no había ningún proceso
 * en ejecución, el proceso pasa a ser ejecutado automáticamente.
 * PRE: El proceso está siendo planificado por el planificador.
 * PRE: El proceso está inactivo.
 */
template<typename T>
void PlanificadorRR<T>::reanudarProceso(const T& elem){

	if (!detenido() && esPlanificado(elem) && !estaActivo(elem)){
		Nodo* buscanodo = buscaNodoElem(elem);

		buscanodo->estaPausado = false;

		if( this->cantProActivos == 0 ) {
			this->actual = buscanodo;
		}

		setCantProActivos(1);
	}
}

/**
 * Detiene la ejecución de todos los procesos en el planificador
 * para atender una interrupción del sistema.
 * PRE: El planificador no está detenido.
 */
template<typename T>
void PlanificadorRR<T>::detener(){
	this->planDetenido = true;
}

/**
 * Reanuda la ejecución de los procesos (activos) en el planificador
 * luego de atender una interrupción del sistema.
 * PRE: El planificador está detenido.
 */
template<typename T>
void PlanificadorRR<T>::reanudar(){
	this->planDetenido = false;
}

/**
 * Informa si el planificador está detenido por el sistema operativo.
 */
template<typename T>
bool PlanificadorRR<T>::detenido() const{
	return this->planDetenido == true;
}

/**
 * Informa si un cierto proceso está siendo planificado por el planificador.
 */
template<typename T>
bool PlanificadorRR<T>::esPlanificado(const T& elem) const{
	Nodo* buscanodo = this->actual;
	int i = this->cantProcesos;

	while (i > 0 && !(buscanodo->elem == elem)){
		i--;
		buscanodo = buscanodo->sig;
	}

	return i != 0;
}

/**
 * Informa si un cierto proceso está activo en el planificador.
 * PRE: El proceso está siendo planificado por el planificador.
 */
template<typename T>
bool PlanificadorRR<T>::estaActivo(const T& elem) const{
	
	if(esPlanificado(elem)){
		Nodo* buscanodo = buscaNodoElem(elem);

		return !buscanodo->estaPausado;
	}

	return false;
}

/**
 * Informa si existen procesos planificados.
 */
template<typename T>
bool PlanificadorRR<T>::hayProcesos() const{
	return (this->actual != NULL && this->cantProcesos > 0);
}

/**
 * Informa si existen procesos activos.
 */
template<typename T>
bool PlanificadorRR<T>::hayProcesosActivos() const{
	return this->cantProActivos > 0;
}

/**
 * Devuelve la cantidad de procesos planificados.
 */
template<typename T>
int PlanificadorRR<T>::cantidadDeProcesos() const{
	return this->cantProcesos;
}

/**
 * Devuelve la cantidad de procesos planificados y activos.
 */
template<typename T>
int PlanificadorRR<T>::cantidadDeProcesosActivos() const{
	return this->cantProActivos;
}

/**
 * Devuelve true si ambos planificadores son iguales.
 */
template<typename T>
bool PlanificadorRR<T>::operator==(const PlanificadorRR<T>& otro) const{
	bool res = false;
	
	res =	(this->cantProcesos == otro.cantProcesos &&
			 this->cantProActivos == otro.cantProActivos &&
			 this->planDetenido == otro.planDetenido);

	if(res){
		Nodo* buscanodoThis = this->actual;
		Nodo* buscanodoOtro = otro.actual;
		int i = this->cantProcesos;
		while(i > 0 && res){
			res = buscanodoThis->elem == buscanodoOtro->elem;
			buscanodoThis = buscanodoThis->sig;
			buscanodoOtro = buscanodoOtro->sig;
			i--;
		}
	}

	return res;
}

/**
 * Debe mostrar los procesos planificados por el ostream (y retornar el mismo).
 * Los procesos deben aparecer en el mismo orden en el que son ejecutados
 * por el planificador. Como la lista es circular, se decidió que el primer
 * proceso que se muestra debe ser el que está siendo ejecutado en ese momento.
 * En el caso particular donde exista al menos un proceso planificado,
 * pero estén todos pausados, se puede comenzar por cualquier proceso.
 * Un proceso inactivo debe ser identificado con el sufijo ' (i)'
 * y el proceso que está siendo ejecutado, de existir, debe ser identificado
 * con el sufijo '*'.
 * PlanificadorRR vacio: []
 * PlanificadorRR con 1 elemento activo: [p0*]
 * PlanificadorRR con 2 elementos inactivos: [p0 (i), p1 (i)]
 * PlanificadorRR con 3 elementos (p0 inactivo, p2 siendo ejecutado: [p2*, p0 (i), p1]
 *
 * OJO: con pX (p0, p1, p2) nos referimos a lo que devuelve el operador <<
 * para cada proceso, es decir, cómo cada proceso decide mostrarse en el sistema.
 * El sufijo 'X' indica el orden relativo de cada proceso en el planificador.
 */
template<typename T>
ostream& PlanificadorRR<T>::mostrarPlanificadorRR(ostream& os) const{
	os << "[";

	if(this->cantProcesos > 0){
		Nodo* buscanodo = this->actual;
		int i = this->cantProcesos;

		while(i > 0){
			os << buscanodo->elem;
			if(i == this->cantProcesos){
				os << "*";
			}

			if(buscanodo->estaPausado){
				os << " (i)";
			}
			
			if(i > 1){
				os << ", ";
			}

			buscanodo = buscanodo->sig;
			i--;
		} //end while
	} // end if grande

	os << "]";
	return os;
}



/********** FUNCIONES AUXILIARES *****************/

template<typename T>
typename PlanificadorRR<T>::Nodo* PlanificadorRR<T>::buscoSigActivo(Nodo* buscanodo){
	int i =  this->cantProcesos;

	while (i > 0 && buscanodo->estaPausado){
		buscanodo = buscanodo->sig;
		i++;
	}

	return buscanodo;
}

//PRE: SE QUE EXISTE
template<typename T>
typename PlanificadorRR<T>::Nodo* PlanificadorRR<T>::buscaNodoElem(const T& elem) const{
	Nodo* buscanodo = this->actual;

	while ( !(buscanodo->elem == elem) ){
		buscanodo = buscanodo->sig;
	}

	return buscanodo;
}

template<typename T>
void PlanificadorRR<T>::setCantProActivos(short i){
	this->cantProActivos += i;
}


#endif // PLANIFICADOR_RR_H_
