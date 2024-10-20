#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

mutex mtx; // Mutex sirve para asegurarse de que diferentes hilos no puedan ingresar al mismo tiempo a una variable, sobreescribiendose entre si.
vector<pair<int, int>> posiciones; // Vector para guardar los autos y su posición final

void carrera(int id, int distancia_total)
{
    int total_avance = 0;
    int lugar = -1;

    // En este while ocurre la carrera en si y se guardan los lugares finales
    while (total_avance < distancia_total)
    {
        int avance = rand() % 11; // Avance aleatorio en metros
        int tiempo = rand() % 401 + 100; // Intervalo de tiempo que define velocidad del auto

        total_avance += avance;

        if (total_avance > distancia_total)
        {
            total_avance = distancia_total;
        }

        {
            lock_guard<mutex> lock(mtx); // Bloquear la consola para asegurar el output
            cout << "Auto" << id + 1 << " avanza " << avance << " metros (total: "
                << total_avance << " metros)" << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(tiempo)); // Se duerme el hilo por la cantidad de tiempo definida anteriormente que representa la velocidad del auto
    }

    {
        lock_guard<mutex> lock(mtx); // Bloquear para asegurar los resultados
        lugar = posiciones.size() + 1;
        posiciones.push_back({id, lugar});
        cout << "Auto" << id + 1 << " termina la carrera en el lugar " << lugar << "!" << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Uso: " << argv[0] << " <distancia_total> <numero_autos>" << endl;
        return 1;
    }

    int distancia_total = stoi(argv[1]);
    int numero_autos = stoi(argv[2]);

    cout << "Distancia total de la carrera: " << distancia_total << " metros." << endl;
    cout << "----------------------------------\n" << endl;
    srand(time(nullptr)); // Inicializar semilla aleatoria

    vector<thread> autos; // Vector que almacena los hilos

    for (int i = 0; i < numero_autos; ++i)
    {
        autos.emplace_back(carrera, i, distancia_total);
    }

    for (auto &t : autos)
    {
        t.join();
    }

    cout << "----------------------------------\n" << endl;
    cout << "Lugar  Auto" << endl;
    cout << "--------------" << endl;
    for (const auto &p : posiciones)
    {
        cout << p.second << "      Auto: " << p.first + 1 << endl;
    }

    return 0;
}
