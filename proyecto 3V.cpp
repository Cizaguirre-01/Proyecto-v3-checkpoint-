#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

struct Alumno {string nombre; string matricula; float  calif[3]; int grupo;};
struct Maestro{string nombre; string materia; int grupo;};
struct Grupo {string nombre; string carrera;};    
float promedioDe(const Alumno& a) {
    return (a.calif[0] + a.calif[1] + a.calif[2]) / 3;
} 

int leerEntero(string mensaje, int min, int max= INT_MAX) { //valida los números entero dentro del rango min y max
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= min && valor <= max) {

            cin.ignore(1000, '\n');
            return valor;
        }
        if (cin.eof())
        {
            break;
        }
        
        cin.clear();               
        cin.ignore(1000, '\n');   
        cout << "Dato invalido. debe ser un numero entre " << min << " y " << max << "." << endl;
    }
    return 0;
    
}



float leerFloat(string mensaje, float min, float max) { // valida los números decimales dentro de min y max 
    float valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= min && valor <= max) {
            cin.ignore(1000, '\n');
            return valor;
        }
        if (cin.eof())
        {
            break;
        }
        
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Dato invalido. Debe ser un numero entre " << min << " y " << max << "." << endl;
    }
    return 0;
}

// estan son las tres funciones auxiliares  que estan dentro del archivo 
void guardarAlumnos(ofstream& archivo, const vector<Alumno>& alum){ // ofstream& es por referencia que escriba directo en el archivo
    archivo<<(int)alum.size()<<endl;                                // guarda cuantos alumnos  hay
    for (int i = 0; i <(int)alum.size(); i++){                      // el for para que ver que va a ver cuantas veces se va a repetir
        archivo<< alum[i].nombre << "|"<<alum[i].matricula<< "|"<<alum[i].calif[0]<< "|"<<alum[i].calif[1]<< "|"<< alum[i].calif[2]<<"|"<<alum[i].grupo<<endl;
        
    }
}
void guardarGrupos(ofstream& archivo, const vector<Grupo>& grup){
    archivo<<(int)grup.size()<<endl;
    for (int i = 0; i <(int) grup.size(); i++){
        archivo<<grup[i].nombre<< "|"<<grup[i].carrera<<endl;
    }

}
void guardarMaestro(ofstream& archivo, const vector<Maestro>& maes){
    archivo<<(int)maes.size()<<endl;
    for (int i = 0; i < (int)maes.size(); i++){
        archivo<<maes[i].nombre<< "|"<<maes[i].materia<<"|" <<maes[i].grupo<< endl;
    }
}





// este void es el que guardara todo en el archivo, los datos de manera directa. caso 5
void escribir ( const vector <Alumno>&alum, const vector <Grupo>&grup, const vector <Maestro>&maes ){
    ofstream archivo("proyecto3.txt");
    if (archivo.fail())
    {
        cout<<" no se puedo abrir el archivo"<<endl;
        exit(1);
    }
    else{
       guardarAlumnos(archivo, alum);
       guardarGrupos(archivo, grup);
       guardarMaestro(archivo, maes);
       archivo.close();
       cout<<" datos exitosamente guardao en proyecto 3"<<endl;
    }
}

// estos son los void para guardar los datos

void cargarAlumnos(ifstream& archivo, vector<Alumno>& alum){
    alum.clear();
    int cantidadAlum;
    archivo>> cantidadAlum;
    archivo.ignore(1000,'\n');
    Alumno a;
    string data;
    for (int i = 0; i < cantidadAlum; i++){
        getline(archivo, a.nombre,'|');       // los | significa que va a leer hasta donde acabe el |
        getline(archivo, a.matricula, '|');
        for (int j = 0; j < 3; j++)
        {
            getline( archivo, data, '|');
            a.calif[j]=stof(data);    // convertimos a variable numerica el (stof) convierte string a un numero decimal float
        }
        getline(archivo, data, '\n');
        a.grupo = stoi(data); //convierte string en un numero entero el (stoi)
        alum.push_back(a);


    }

}
void cargarGrupos(ifstream& archivo, vector<Grupo>& grup){
    grup.clear(); 
    int cantidadGrup;
    archivo>> cantidadGrup;
    archivo.ignore(1000,'\n');
    Grupo g;
    for (int i = 0; i < cantidadGrup; i++)
    {
        getline(archivo, g.nombre,'|');
        getline(archivo, g.carrera,'\n');
        grup.push_back(g);
            
    }

}
void cargarMaestro(ifstream& archivo,vector<Maestro>& maes){
    maes.clear();
    int cantidadMaes;
    archivo>> cantidadMaes;
    archivo.ignore(1000,'\n');
    Maestro m;
    string data;
    for (int i = 0; i < cantidadMaes; i++){
        getline(archivo, m.nombre, '|');
        getline(archivo, m.materia, '|');
        getline(archivo, data, '\n');
        m.grupo = stoi(data);
        maes.push_back(m);


    }
        

}


void cargaDeData( vector<Alumno>&alum, vector <Grupo>&grup, vector<Maestro>&maes ){
    ifstream archivo("proyecto3.txt");
    if (archivo.fail())
    {
        cout<<" no hay datos guardados";
        return;
    }
    else{
        cargarAlumnos(archivo,alum);
        cargarGrupos(archivo,grup);
        cargarMaestro(archivo,maes);

    
        
       archivo.close();
       cout << "datos cargados de manera exitosa." << endl;
    
    } 


    
}



// caso 1
void registrarAlumnos( vector<Alumno>&alum, vector<Grupo>&grup){
    int n=leerEntero(" cuantos alumnos va a registrar",1,INT_MAX);
    for (int i=0;i<n;i++ ){
        Alumno a;
        cout<<"ingrese nombre del alumno"<<alum.size()+1<<":"<<endl;
        getline(cin, a.nombre);
        cout<<" ingrese matricula del alumno :";
        getline(cin, a.matricula);
        string nombreGrupo;
        cout<< " Ingrese el nombre de un grupo donde esta el alumno: " <<a.nombre<< " : " <<endl;
        getline(cin,nombreGrupo);

        a.grupo = -1;
        for (int g = 0; g < (int)grup.size(); g++) {
            if (grup[g].nombre == nombreGrupo) a.grupo = g;
        }

        if (a.grupo == -1) {
            Grupo nuevo;
            nuevo.nombre = nombreGrupo;
            nuevo.carrera = "";
            grup.push_back(nuevo);
            a.grupo = grup.size() - 1;
        }

           
        for(int j=0;j<3;j++){
                    
        a.calif[j]=leerFloat("ingrese calificacion" + to_string(j+1)+ "del alumno:",0,10);
                    
        }
        alum.push_back(a);
               
            
            
    }   
    

}

// caso 2
void registrarGrupos(vector<Grupo>& grup){
    int n=leerEntero(" cuantos grupos va a registrar",1,INT_MAX);
    for (int i=0;i<n;i++ ){
                
        Grupo g;
        cout<<" ingrese el nombre del grupo"<<grup.size()+1<<":"<<endl;
        getline(cin, g.nombre);
        cout<<"ingrese la carrera asociada : ";
        getline(cin, g.carrera);
        grup.push_back(g);
    }

        
    cout << "Grupos existentes:" << endl;
    for (int g = 0; g < (int)grup.size(); g++) {
        cout << "Grupo " << g + 1 << ": " << grup[g].nombre << endl;
                
    }

}
//caso 3

void registrarMaestros(vector<Maestro>& maes , const vector<Grupo>& grup){
    

    int n=leerEntero("cuantos maestros va a registrar: ",1);
    

    for(int i=0;i<n;i++){
        Maestro m;
        cout<<"ingrese los nombres completos de los maestros: ";
        getline(cin, m.nombre);
        cout<<" Que materia imparte: ";
        getline(cin, m.materia);
                
        if (!grup.empty()) {
            cout << "Grupos registrados:" << endl;
            for (int g = 0; g < (int)grup.size(); g++) {
                cout << "["<<g+1<<"]" << grup[g].nombre << endl;
            }
        }
        int sel;
        do {
            cout << "Elige el grupo al que da clases " << m.nombre << ": ";
            cin >> sel;
        } while (sel < 1 || sel > (int)grup.size());
        cin.ignore();

        m.grupo = sel - 1;
        maes.push_back(m);



    }

}
// este es el reporte que aparece en la terminal en el codigo  caso 4 reporte academico 
void Reporte( const vector<Alumno>& alum, const  vector<Grupo>& grup, const vector<Maestro>& maes ){
    cout<< " promedios de cada almumno "<<endl;
            
    for(int i=0;i< (int)alum.size();i++){
        cout<<alum[i].nombre<<"("<<alum[i].matricula<<")"<<"promedio:"<<promedioDe(alum[i])<<endl;
    }
       
            
    cout<<"alumno con mejor promedio por grupo"<<endl;
           
        for(int g=0; g< (int)grup.size();g++){
         int mejor=-1;
         for(int i=0; i<(int)alum.size();i++){
            if (alum[i].grupo==g &&
                (mejor==-1 || promedioDe (alum[i])> promedioDe(alum[mejor]))){
                mejor= i;
            }
        }
        cout<< grup[g].nombre<<": ";
        if( mejor==-1)cout<<" sin alumnos"<<endl;
        else cout<< alum[mejor].nombre<<"("<<promedioDe(alum[mejor])<<")"<<endl;

    }
    cout << "cantidad de alumnos que hay por carrera" << endl;
    vector<string> carreras;
    for (int g = 0; g < (int)grup.size(); g++) {
        bool existe = false;
        for (int k = 0; k < (int)carreras.size(); k++) {
            if (carreras[k] == grup[g].carrera) existe = true;
        }
        if (!existe) carreras.push_back(grup[g].carrera);
    }
    for (int k = 0; k < (int)carreras.size(); k++) {
        int contador = 0;
        for (int i = 0; i < (int)alum.size(); i++) {
            if (grup[alum[i].grupo].carrera == carreras[k]) contador++;
        }
        cout << carreras[k] << " : " << contador << " alumnos" << endl;

    }
    cout << "\n Maestros por grupo" << endl;
    for (int i = 0; i < (int)maes.size(); i++) {
        cout << maes[i].nombre << " - " << maes[i].materia<< " - grupo: " << grup[maes[i].grupo].nombre << endl;

    }

}
// funciones auxiliares para el repote que estara en un archivo  este compara el mejor promedio de grupos 
void ordenAlumnosPromedio(vector<Alumno>& copia){
    
    for (int i = 0; i < (int)copia.size(); i++)
    {
        for (int j = i + 1; j < (int)copia.size(); j++)
        {
            if (promedioDe(copia[i]) <promedioDe(copia[j]))
            {
                Alumno aux= copia[i];
                copia[i]= copia[j];
                copia[j]=aux;
            }
            
        }
        
    }
    

}
//mas funciones auxiliares  este va a hacer la presentación y formato del archivo
void ReporteArchiv ( const vector<Alumno>& ordenados, const vector<Grupo>& grup, const vector<Maestro>& maes){
    ofstream arch("Reporte.txt");
    if (arch.fail())
    {
        cout<<"no se ha podido abrir el archivo"<<endl;
        return;
    }
    else{
       arch<<"-------------------------------------------------------------"<<endl;
       arch<<"           alumnos ordenados por promedio                    "<<endl;
       arch<<"-------------------------------------------------------------"<<endl;
       for (int i = 0; i < (int)ordenados.size(); i++)
       {
        string nombreGrupo= (ordenados[i].grupo >= 0 && ordenados[i].grupo< (int)grup.size())
        ? grup[ordenados[i].grupo].nombre : "sin grupo";
        arch<<i + 1 <<" "<<ordenados[i].nombre
        << " | matricula: "<< ordenados[i].matricula
        <<"  | grupo: "<< nombreGrupo
        <<". |Promedio:   "<<promedioDe(ordenados[i])<<endl;
       }
       
    }
    arch.close();
    cout<<" el reporte fue generado"<<endl;

}

// este es el oficial que guarda todo y genera el reporte ya en el archivo 
void verdaderoReporteArchivo(const vector<Alumno>& alum, const vector<Grupo>& grup, const vector<Maestro>& maes){
    vector<Alumno> copia = alum;
    ordenAlumnosPromedio(copia);
    ReporteArchiv(copia, grup, maes);

}



int main()
{
    vector<Alumno> alum;
    vector<Grupo> grup;
    vector<Maestro> maes;

    int opcion;
    do {
        cout<<"---------------------------------------------------------------------------------------"<<endl;
        cout << "Bienvenido al menu academico, elige una opcion valida del menú "<<endl;
        cout << "[1] Registrar uno o mas alumnos,registrar calificaciónes,asociar grupos "<<endl;
        cout << "[2] Registrar y crear nuevos grupos y carreras"<<endl;
        cout << "[3] Información de maestros,asignarles materias y asociarlos con los grupos "<<endl;
        cout << "[4] Mostrar reporte academico "<<endl;
        cout << "[5] Guardar "<<endl;
        cout << "[6] Cargar" <<endl;
        cout << "[7] Generar un reporte en el archivo "<<endl;
        cout << "[8] Salir se cerrará el ciclo del menú "<<endl;
        opcion= leerEntero("elegir una de las opciones que desees ejecutar :",1,8);
        cout<<"---------------------------------------------------------------------------------------"<<endl;

        switch (opcion)
        {
        case 1:{
            
            registrarAlumnos(alum,grup);  
            
            }
            break;
        
        
            
        
        case 2:{
            cout<<"Registrar y crear nuevos grupos y carreras ";
            registrarGrupos(grup);
            }

            break;
        

        case 3:{
            if (grup.empty()) {
                cout << "(primero haga la opcion 1)" << endl;
                break;
            }
            registrarMaestros(maes,grup);
            break;


        }
        case 4:{
           
            Reporte(alum,grup,maes);
            break;
        }
        
        case 5:{

            escribir(alum,grup,maes);
            break;

        }
        case 6:{
           cargaDeData(alum,grup,maes);
            

            
            break;
        }
        case 7:{
            verdaderoReporteArchivo(alum,grup,maes);
            break;

        }
        case 8:{
            cout << "salida" << endl;
            break;
        }

        default:
        cout << "opcion desconocida" << endl;
        break;
    }
        
    
    

         
    } while (opcion != 8);
    return 0;




}
