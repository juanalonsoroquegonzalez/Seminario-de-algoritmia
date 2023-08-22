#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Paquete
{
private:

    int id;
    std::string origen;
    std::string destino;
    double peso;

public:
    Paquete(int _id, const std::string& _origen, const std::string& _destino, double _peso)
        : id(_id), origen(_origen), destino(_destino), peso(_peso) {
    }
    int getId() const {
        return id;
    }
    std::string getOrigen() const {
        return origen;
    }
    std::string getDestino() const {
        return destino;
    }
    double getPeso() const {
        return peso;
    }
};

class NodoPaquete {
public:

    Paquete paquete;
    NodoPaquete* siguiente;

    NodoPaquete(const Paquete& _paquete) : paquete(_paquete), siguiente(nullptr) {}
};

class Paqueteria {
private:

    NodoPaquete* primerNodo;

public:
    Paqueteria() : primerNodo(nullptr) {}

    void insertarAlInicio(const Paquete& paquete) {
        NodoPaquete* nuevoNodo = new NodoPaquete(paquete);
        nuevoNodo->siguiente = primerNodo;
        primerNodo = nuevoNodo;
    }

    void eliminarAlInicio() {
        if (primerNodo) {
            NodoPaquete* nodoEliminar = primerNodo;
            primerNodo = primerNodo->siguiente;
            delete nodoEliminar;
        }
    }

    void mostrar() const {
        NodoPaquete* nodoActual = primerNodo;
        while (nodoActual) {
            std::cout << "ID: " << nodoActual->paquete.getId() << " | "
                      << "Origen: " << nodoActual->paquete.getOrigen() << " | "
                      << "Destino: " << nodoActual->paquete.getDestino() << " | "
                      << "Peso: " << nodoActual->paquete.getPeso() << " kg" << std::endl;
            nodoActual = nodoActual->siguiente;
        }
    }

    void guardar(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            NodoPaquete* nodoActual = primerNodo;
            while (nodoActual) {
                archivo << nodoActual->paquete.getId() << ","
                        << nodoActual->paquete.getOrigen() << ","
                        << nodoActual->paquete.getDestino() << ","
                        << nodoActual->paquete.getPeso() << "\n";
                nodoActual = nodoActual->siguiente;
            }

            archivo.close();

            std::cout << "Datos guardados en el archivo " << nombreArchivo << std::endl;
        } else {
            std::cerr << "No se pudo abrir el archivo " << nombreArchivo << " para guardar." << std::endl;
        }
    }

    void recuperar(const std::string& nombreArchivo) {
        std::ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            while (primerNodo) {
                NodoPaquete* nodoEliminar = primerNodo;
                primerNodo = primerNodo->siguiente;
                delete nodoEliminar;
            }

            std::string linea;

            while (std::getline(archivo, linea)) {
                std::istringstream parrafo(linea);
                std::string campo;
                int id;
                std::string origen, destino;
                double peso;

                // Leer campos usando el operador de extracción >>
                if (std::getline(parrafo, campo, ','))
                    id = std::stoi(campo);
                if (std::getline(parrafo, origen, ','))
                    if (std::getline(parrafo, destino, ','))
                        if (std::getline(parrafo, campo, ','))
                            peso = std::stod(campo);

                Paquete paquete(id, origen, destino, peso);
                insertarAlInicio(paquete);
            }
            archivo.close();
            std::cout << "Datos recuperados desde el archivo " << nombreArchivo << std::endl;
        } else {
            std::cerr << "No se pudo abrir el archivo " << nombreArchivo << " para recuperar datos." << std::endl;
        }
    }

    ~Paqueteria() {
        while (primerNodo) {
            NodoPaquete* nodoEliminar = primerNodo;
            primerNodo = primerNodo->siguiente;
            delete nodoEliminar;
        }
    }
};

int main() {
    Paqueteria paqueteria;
    int opcion;
    int id_;
    std::string origen_;
    std::string destino_;
    double peso_;
    while (true){
        std::cout << "------------------ PAQUETERÍA --------------------\n\n";
        std::cout << "1.- Agregar paquete\n";
        std::cout << "2.- Eliminar paquete\n";
        std::cout << "3.- Mostrar paquetes\n";
        std::cout << "4.- Guardar paquetes\n";
        std::cout << "5.- Recuperar paquetes\n";
        std::cout << "6.- Salir\n\n";
        std::cout << "¿Qué quieres hacer? ";
        std::cin >> opcion;

        switch(opcion){
        case 1:
                std::cout << "Ingresa el ID: ";
                std::cin >> id_;
                std::cout << "Ingresa el Origen: ";
                std::cin >> origen_;
                std::cout << "Ingresa el Destino: ";
                std::cin >> destino_;
                std::cout << "Ingresa el Peso: ";
                std::cin >> peso_;
                paqueteria.insertarAlInicio(Paquete(id_, origen_, destino_, peso_));
                std::cout << "Paquete agregado.\n";
                system("PAUSE()");
                system("cls");
                break;
            case 2:
                paqueteria.eliminarAlInicio();
                std::cout << "Primer paquete eliminado.\n";
                system("PAUSE()");
                system("cls");
                break;
            case 3:
                paqueteria.mostrar();
                system("PAUSE()");
                system("cls");
                break;
            case 4:
                paqueteria.guardar("paquetes.txt");
                std::cout << "Paquetes guardados en 'paquetes.txt'.\n";
                system("PAUSE()");
                system("cls");
                break;
             case 5:
                paqueteria.recuperar("paquetes.txt");
                std::cout << "Paquetes recuperados desde 'paquetes.txt'.\n";
                system("PAUSE()");
                system("cls");
                break;
            case 6:
                std::cout << "Saliendo del programa.\n";
                return 0;
            default:
                std::cout << "Opción inválida. Inténtalo de nuevo.\n";
                break;
        }
    }
    return 0;
}
