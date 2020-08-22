#include <iostream>
#include <vector>

#include "PC.hpp"

using namespace std;

int main()
{
    vector<PC> listaPCS;
    bool vive = true;
    while (vive)
    {
        std::cout << "1. Agregar PC"
                  << "\n"
                  << "2. Ingresar a PC \n"
                  << "0. Salir" << std::endl;

        int opUsuario;
        cin >> opUsuario;

        switch (opUsuario)
        {
        case 0:
            return (0);
            break;
        case 1:
        {
            std::cout << "Ingrese el hostname:" << std::endl;
            string hostname, ip, mask;
            cin >> hostname;
            std::cout << "Ingrese la ip:" << std::endl;
            cin >> ip;
            std::cout << "Ingrese la mascara de red:" << std::endl;
            cin >> mask;

            PC pcTemp(ip, hostname, mask);
            listaPCS.push_back(pcTemp);
            cout << endl;
            break;
        }

        case 2:
        {
            std::cout << "Ingrese el indice de la PC a la que desea acceder: " << std::endl;
            for (size_t i = 0; i < listaPCS.size(); i++)
            {
                std::cout << i + 1 << ". " << listaPCS.at(i).getHostname() << std::endl;
            }

            int indPcAIngresar;
            cin >> indPcAIngresar;
            indPcAIngresar--;

            cout << "\n"
                 << endl;

            bool usuarioActivo = true;
            while (usuarioActivo)
            {
                cout << listaPCS.at(indPcAIngresar).getHostname() << "#";
                string comandoAEjecutar;
                cin >> comandoAEjecutar;

                if (comandoAEjecutar == "show")
                {
                    PC::show(listaPCS.at(indPcAIngresar));
                }
                else if (comandoAEjecutar == "exit")
                {
                    usuarioActivo = false;
                }
                else if (comandoAEjecutar.substr(0, 4) == "ping")
                {
                    string ipABuscar = comandoAEjecutar.substr(5);
                    PC::ping(ipABuscar, listaPCS.at(indPcAIngresar), listaPCS);
                }
                else
                {
                    std::cout << "Ingrese un comando valido." << std::endl;
                }
            }
        }
        break;
        default:
            std::cout << "Ingrese una opcion valida" << std::endl;
            break;
        }
    }
}