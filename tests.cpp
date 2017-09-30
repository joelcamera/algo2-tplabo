// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include <algorithm>
#include "mini_test.h"
#include "PlanificadorRR.h"

using namespace std;

string remove_spaces(const string& s) {
  string out(s);
  out.erase(remove(out.begin(), out.end(), ' '), out.end());
  out.erase(remove(out.begin(), out.end(), '\n'), out.end());
  return out;
}

template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
}

/**
 * Crea un planificador sin porocesos.
 */
void test_planificadorVacio(){
  PlanificadorRR<int> planificador;
  ASSERT_EQ(planificador.hayProcesos(), false);
  ASSERT_EQ(planificador.hayProcesosActivos(), false);
  ASSERT_EQ(to_s(planificador), "[]");
}

void test_crearPlanificador(){
  PlanificadorRR<int> p1;
  ASSERT( !p1.hayProcesos() );
  ASSERT( !p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 0);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 0);

  PlanificadorRR<char> p2;
  ASSERT( !p2.hayProcesos() );
  ASSERT( !p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 0);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 0);

  PlanificadorRR<string> p3;
  ASSERT( !p3.hayProcesos() );
  ASSERT( !p3.hayProcesosActivos() );
  ASSERT( !p3.detenido() );
  ASSERT_EQ(p3.cantidadDeProcesos(), 0);
  ASSERT_EQ(p3.cantidadDeProcesosActivos(), 0);

  PlanificadorRR< PlanificadorRR<int> > p4;
  ASSERT( !p4.hayProcesos() );
  ASSERT( !p4.hayProcesosActivos() );
  ASSERT( !p4.detenido() );
  ASSERT_EQ(p4.cantidadDeProcesos(), 0);
  ASSERT_EQ(p4.cantidadDeProcesosActivos(), 0);

}

void test_crearPlanPorCopia(){
  PlanificadorRR<int> p1;
  PlanificadorRR<int> p2(p1);
  ASSERT( p1 == p2 );

  //agrego algo a p1, no deberia haberse agregado en p2
  //y viceversa
  p1.agregarProceso(1);
  p2.agregarProceso(2);
  ASSERT( !(p1 == p2) );

  //agrego mas elementos a p1 y despues creo otro planificador
  for(int i = 0; i < 5; i++){
    p1.agregarProceso(i);
  }
  ASSERT( !(p1 == p2) );

  PlanificadorRR<int> p3(p1);
  ASSERT( p1 == p3 );
  ASSERT( !(p2 == p3) );

  //agrego elementos a p3 y creo otro planificador con este
  for(int i = 10; i < 15; i++){
    p3.agregarProceso(i);
  }
  ASSERT( !(p1 == p3) );
  ASSERT( !(p2 == p3) );

  PlanificadorRR<int> p4(p3);
  ASSERT( (p4 == p3) );
}

void test_agregarYEliminar(){
  PlanificadorRR<int> p1;
  ASSERT( !p1.hayProcesos() );
  ASSERT( !p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 0);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 0);

  //pregunto si hay algunos elementos en el pl vacio
  ASSERT( !p1.esPlanificado(1) );
  ASSERT( !p1.esPlanificado(2) );
  ASSERT( !p1.esPlanificado(3) );
  ASSERT( !p1.esPlanificado(4) );
  ASSERT( !p1.esPlanificado(5) );

  //agrego elementos
  p1.agregarProceso(1);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 1);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 1);
  ASSERT( p1.esPlanificado(1) );

  p1.agregarProceso(2);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 2);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 2);
  ASSERT( p1.esPlanificado(2) );

  p1.agregarProceso(3);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 3);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 3);
  ASSERT( p1.esPlanificado(3) );

  p1.agregarProceso(4);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 4);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 4);
  ASSERT( p1.esPlanificado(4) );

  p1.agregarProceso(5);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 5);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 5);
  ASSERT( p1.esPlanificado(5) );

  //agrego algunos que ya agregue, no deberian agregarse
  p1.agregarProceso(1);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 5);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 5);
  ASSERT( p1.esPlanificado(1) );

  p1.agregarProceso(4);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 5);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 5);
  ASSERT( p1.esPlanificado(4) );

  //elimino los procesos hasta que quede vacio
  //en este caso siempre estoy eliminando el actual
  p1.eliminarProceso(1);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 4);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 4);
  ASSERT( !p1.esPlanificado(1) );

  p1.eliminarProceso(2);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 3);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 3);
  ASSERT( !p1.esPlanificado(2) );

  p1.eliminarProceso(3);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 2);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 2);
  ASSERT( !p1.esPlanificado(3) );

  p1.eliminarProceso(4);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 1);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 1);
  ASSERT( !p1.esPlanificado(4) );

  p1.eliminarProceso(5);
  ASSERT( !p1.hayProcesos() );
  ASSERT( !p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 0);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 0);
  ASSERT( !p1.esPlanificado(5) );

  //QUEDO VACIO
  //agrego 5 elementos y voy borrando el ultimo siempre
  p1.agregarProceso(1);
  p1.agregarProceso(2);
  p1.agregarProceso(3);
  p1.agregarProceso(4);
  p1.agregarProceso(5);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 5);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 5);
  ASSERT( p1.esPlanificado(1) );
  ASSERT( p1.esPlanificado(2) );
  ASSERT( p1.esPlanificado(3) );
  ASSERT( p1.esPlanificado(4) );
  ASSERT( p1.esPlanificado(5) );

  p1.eliminarProceso(5);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 4);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 4);
  ASSERT( !p1.esPlanificado(5) );

  p1.eliminarProceso(4);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 3);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 3);
  ASSERT( !p1.esPlanificado(4) );

  p1.eliminarProceso(3);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 2);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 2);
  ASSERT( !p1.esPlanificado(3) );

  p1.eliminarProceso(2);
  ASSERT( p1.hayProcesos() );
  ASSERT( p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 1);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 1);
  ASSERT( !p1.esPlanificado(2) );

  p1.eliminarProceso(1);
  ASSERT( !p1.hayProcesos() );
  ASSERT( !p1.hayProcesosActivos() );
  ASSERT( !p1.detenido() );
  ASSERT_EQ(p1.cantidadDeProcesos(), 0);
  ASSERT_EQ(p1.cantidadDeProcesosActivos(), 0);
  ASSERT( !p1.esPlanificado(1) );

  //QUEDO VACIO P1


  //NUEVO TEST CON CHAR
  PlanificadorRR<char> p2;

  ASSERT( !p2.hayProcesos() );
  ASSERT( !p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 0);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 0);

  //pregunto si hay algunos elementos en el pl vacio
  ASSERT( !p2.esPlanificado('a') );
  ASSERT( !p2.esPlanificado('b') );
  ASSERT( !p2.esPlanificado('c') );
  ASSERT( !p2.esPlanificado('d') );
  ASSERT( !p2.esPlanificado('e') );

  //agrego elementos
  p2.agregarProceso('a');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 1);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 1);
  ASSERT( p2.esPlanificado('a') );

  p2.agregarProceso('b');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 2);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 2);
  ASSERT( p2.esPlanificado('b') );

  p2.agregarProceso('c');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 3);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 3);
  ASSERT( p2.esPlanificado('c') );

  p2.agregarProceso('d');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 4);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 4);
  ASSERT( p2.esPlanificado('d') );

  p2.agregarProceso('e');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 5);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 5);
  ASSERT( p2.esPlanificado('e') );

  //agrego algunos que ya agregue, no deberian agregarse
  p2.agregarProceso('a');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 5);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 5);
  ASSERT( p2.esPlanificado('a') );

  p2.agregarProceso('e');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 5);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 5);
  ASSERT( p2.esPlanificado('e') );

  //elimino los procesos hasta que quede vacio
  //en este caso siempre estoy eliminando el actual
  p2.eliminarProceso('a');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 4);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 4);
  ASSERT( !p2.esPlanificado('a') );

  p2.eliminarProceso('b');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 3);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 3);
  ASSERT( !p2.esPlanificado('b') );

  p2.eliminarProceso('c');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 2);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 2);
  ASSERT( !p2.esPlanificado('c') );

  p2.eliminarProceso('d');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 1);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 1);
  ASSERT( !p2.esPlanificado('d') );

  p2.eliminarProceso('e');
  ASSERT( !p2.hayProcesos() );
  ASSERT( !p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 0);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 0);
  ASSERT( !p2.esPlanificado('e') );

  //agrego 5 elementos y voy borrando el ultimo siempre
  p2.agregarProceso('a');
  p2.agregarProceso('b');
  p2.agregarProceso('c');
  p2.agregarProceso('d');
  p2.agregarProceso('e');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 5);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 5);
  ASSERT( p2.esPlanificado('a') );
  ASSERT( p2.esPlanificado('b') );
  ASSERT( p2.esPlanificado('c') );
  ASSERT( p2.esPlanificado('d') );
  ASSERT( p2.esPlanificado('e') );

  p2.eliminarProceso('e');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 4);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 4);
  ASSERT( !p2.esPlanificado('e') );

  p2.eliminarProceso('d');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 3);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 3);
  ASSERT( !p2.esPlanificado('d') );

  p2.eliminarProceso('c');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 2);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 2);
  ASSERT( !p2.esPlanificado('e') );

  p2.eliminarProceso('b');
  ASSERT( p2.hayProcesos() );
  ASSERT( p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 1);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 1);
  ASSERT( !p2.esPlanificado('b') );

  p2.eliminarProceso('a');
  ASSERT( !p2.hayProcesos() );
  ASSERT( !p2.hayProcesosActivos() );
  ASSERT( !p2.detenido() );
  ASSERT_EQ(p2.cantidadDeProcesos(), 0);
  ASSERT_EQ(p2.cantidadDeProcesosActivos(), 0);
  ASSERT( !p2.esPlanificado('a') );

  //QUEDO VACIO
}

void test_actualSiguiente(){
  //en este test todos los procesos estan activos siempre

  PlanificadorRR<int> p;
  for (int i = 0; i < 10; i++){
    p.agregarProceso(i);
  }

  for(int i = 0; i < 10; i++){
    ASSERT_EQ(p.procesoEjecutado(), i);
    p.ejecutarSiguienteProceso();
  }

  //elimino un par para ver el siguiente
  ASSERT_EQ(p.procesoEjecutado(), 0);

  //elimino el primer proceso
  p.eliminarProceso(0);
  ASSERT( !p.esPlanificado(0) );

  for (int i = 1; i < 10; i++){
    ASSERT_EQ(p.procesoEjecutado(), i);
    p.ejecutarSiguienteProceso();
  }

  p.eliminarProceso(1);
  ASSERT( !p.esPlanificado(1) );
  for (int i = 2; i < 10; i++){
    ASSERT_EQ(p.procesoEjecutado(), i);
    p.ejecutarSiguienteProceso();
  }

  p.eliminarProceso(5);
  ASSERT( !p.esPlanificado(5) );
  for (int i = 2; i < 9; i++){
    if (i < 5){
      ASSERT_EQ(p.procesoEjecutado(), i);
    } else {
      ASSERT_EQ(p.procesoEjecutado(), i+1);
    }
    
    p.ejecutarSiguienteProceso();
  }

  ASSERT_EQ(p.procesoEjecutado(), 2);


  //que pasa si hay un solo proceso?
  PlanificadorRR<int> p2;
  p2.agregarProceso(1);
  p2.ejecutarSiguienteProceso();
  ASSERT_EQ(p2.procesoEjecutado(), 1);

}

void test_pausarReanudar(){
  //planificador con 3 procesos, pauso el actual
  //se mueve entre los otros dos
  PlanificadorRR<int> p;
  p.agregarProceso(1);
  p.agregarProceso(2);
  p.agregarProceso(3);
  ASSERT_EQ(p.cantidadDeProcesos(), 3);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 3);
  ASSERT_EQ(p.procesoEjecutado(), 1);

  p.pausarProceso(1);
  ASSERT_EQ(p.cantidadDeProcesos(), 3);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 2);
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);

  p.pausarProceso(2);
  ASSERT_EQ(p.cantidadDeProcesos(), 3);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 1);
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);

  //este pausar hace que pase al siguiente y si esta pausado
  //continue, despausandolo (nunca estan todos pausados)
  p.pausarProceso(3);
  ASSERT_EQ(p.cantidadDeProcesos(), 3);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 0);

  p.reanudarProceso(2);
  ASSERT_EQ(p.cantidadDeProcesos(), 3);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 1);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);

  p.reanudarProceso(3);
  ASSERT_EQ(p.cantidadDeProcesos(), 3);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);

  p.reanudarProceso(1);
  ASSERT_EQ(p.cantidadDeProcesos(), 3);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 1);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 1);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
}

void test_detenerReanudarPlan(){
  //primero pruebo con un planificador vacio.
  //lo detengo y no puedo agregar nada
  PlanificadorRR<int> p;
  p.detener();
  ASSERT( p.detenido() );
  p.agregarProceso(1);
  p.agregarProceso(2);
  p.agregarProceso(3);
  p.agregarProceso(4);
  p.agregarProceso(5);
  ASSERT_EQ(p.cantidadDeProcesos(), 0);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 0);

  //reanudo, agrego cosas y lo detengo de nuevo, no puedo
  //avanzar ni borrar ni agregar nada.
  p.reanudar();
  ASSERT( !p.detenido() );
  p.agregarProceso(1);
  p.agregarProceso(2);
  p.agregarProceso(3);
  p.agregarProceso(4);
  p.agregarProceso(5);
  ASSERT_EQ(p.cantidadDeProcesos(), 5);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 5);
  p.detener();
  ASSERT( p.detenido() );
  p.eliminarProceso(1);
  ASSERT_EQ(p.cantidadDeProcesos(), 5);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 5);
  p.eliminarProceso(2);
  ASSERT_EQ(p.cantidadDeProcesos(), 5);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 5);
  p.eliminarProceso(3);
  ASSERT_EQ(p.cantidadDeProcesos(), 5);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 5);
  p.eliminarProceso(4);
  ASSERT_EQ(p.cantidadDeProcesos(), 5);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 5);
  p.eliminarProceso(5);
  ASSERT_EQ(p.cantidadDeProcesos(), 5);
  ASSERT_EQ(p.cantidadDeProcesosActivos(), 5);
  p.ejecutarSiguienteProceso();
  p.ejecutarSiguienteProceso();
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 1);

  //quito el detener
  p.reanudar();
  ASSERT( !p.detenido() );
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 2);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 4);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 5);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 1);

  p.eliminarProceso(1);
  p.eliminarProceso(2);
  ASSERT_EQ(p.procesoEjecutado(), 3);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 4);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 5);
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(p.procesoEjecutado(), 3);
}

void test_operIgualdad(){
  PlanificadorRR<int> p1;
  PlanificadorRR<int> p2;

  //vacios son iguales
  ASSERT(p1 == p2);

  //agrego mismos elementos y son iguales
  for(int i = 0; i < 5; i++){
    p1.agregarProceso(i);
    ASSERT( !(p1 == p2) );
    p2.agregarProceso(i);
    ASSERT(p1 == p2);
  }

  //detengo uno y son distintos
  p1.detener();
  ASSERT( !(p1 == p2) );
  //detengo el otro y son iguales
  p2.detener();
  ASSERT(p1 == p2);
  //reanudo uno y son distintos
  p1.reanudar();
  ASSERT( !(p1 == p2) );
  //reanudo el otro y son iguales
  p2.reanudar();
  ASSERT(p1 == p2);

  //borro uno y son distintos
  //borro el ultimo
  p1.eliminarProceso(4);
  ASSERT( !(p1 == p2) );
  p2.eliminarProceso(4);
  ASSERT(p1 == p2);

  //elimino los elementos y son iguales
  for(int i = 0; i < 4; i++){
    p2.eliminarProceso(i);
    ASSERT( !(p1 == p2) );
    p1.eliminarProceso(i);
    ASSERT(p1 == p2);
  }
}

void test_mostrarPlanificador(){
  PlanificadorRR<int> p;
  //planificador vacio
  ASSERT_EQ(to_s(p), "[]");

  //agrego elementos e imprimo
  p.agregarProceso(1);
  ASSERT_EQ(to_s(p), "[1*]");
  p.agregarProceso(2);
  ASSERT_EQ(to_s(p), "[1*, 2]");
  p.agregarProceso(3);
  ASSERT_EQ(to_s(p), "[1*, 2, 3]");
  p.agregarProceso(4);
  ASSERT_EQ(to_s(p), "[1*, 2, 3, 4]");

  //hago los ultimos dos inactivos
  p.pausarProceso(3);
  ASSERT_EQ(to_s(p), "[1*, 2, 3 (i), 4]");
  p.pausarProceso(4);
  ASSERT_EQ(to_s(p), "[1*, 2, 3 (i), 4 (i)]");

  //avanzo y tendria que ser el 2 el primero
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[2*, 3 (i), 4 (i), 1]");
  //avanzo y tendria que ser el 1 el primero
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[1*, 2, 3 (i), 4 (i)]");

  //deja de estar inactivo el 4, elimino el 3 y agrego el 5
  //y lo hago inactivo
  p.reanudarProceso(4);
  p.eliminarProceso(3);
  p.agregarProceso(5);
  p.pausarProceso(5);
  ASSERT_EQ(to_s(p), "[1*, 2, 4, 5 (i)]");

  //avanzo y tiene que ser el 2 el que se ejecuta
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[2*, 4, 5 (i), 1]");
  //avanzo y tiene que ser el 4 el que se ejecuta
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[4*, 5 (i), 1, 2]");
  //avanzo y tiene que ser el 1 el que se ejecuta
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[1*, 2, 4, 5 (i)]");

  //reanudo el 5 y doy la vuelta completa de ejecucion
  p.reanudarProceso(5);
  ASSERT_EQ(to_s(p), "[1*, 2, 4, 5]");
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[2*, 4, 5, 1]");
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[4*, 5, 1, 2]");
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[5*, 1, 2, 4]");
  p.ejecutarSiguienteProceso();
  ASSERT_EQ(to_s(p), "[1*, 2, 4, 5]");
}


int main(){

  RUN_TEST(test_planificadorVacio);
  RUN_TEST(test_crearPlanificador);
  RUN_TEST(test_crearPlanPorCopia);
  RUN_TEST(test_agregarYEliminar);
  RUN_TEST(test_actualSiguiente);
  RUN_TEST(test_pausarReanudar);
  RUN_TEST(test_detenerReanudarPlan);
  RUN_TEST(test_operIgualdad);
  RUN_TEST(test_mostrarPlanificador);

  return 0;
}
