#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#ifndef PC_H
#define PC_H

using namespace std;

string toBinary(int n)
{
    long long binaryNumber = 0;
    int remainder, i = 1, step = 1;

    while (n != 0)
    {
        remainder = n % 2;
        n /= 2;
        binaryNumber += remainder * i;
        i *= 10;
    }
    string numeroString = to_string(binaryNumber);

    return numeroString;
}

vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while (getline(ss, tok, delimiter))
    {
        internal.push_back(tok);
    }

    return internal;
}

class PC
{
private:
    string ip, hostname, mask;

public:
    PC();
    PC(string _ip, string _hostname, string _mask)
    {
        ip = _ip;
        hostname = _hostname;
        mask = _mask;
    };

    string getIP()
    {
        return ip;
    }
    string getNetmask()
    {
        return mask;
    }
    static void ping(string ipRecibida, PC usuarioActual, vector<PC> listaPCS)
    {
        bool ipEncontrada = false;
        int indPCAPingear = 0;
        string arrIp[100];

        for (size_t i = 0; i < listaPCS.size(); i++)
        {
            if (listaPCS.at(i).getIP() == ipRecibida)
            {
                ipEncontrada = true;
                indPCAPingear = i;
            }
        }

        if (ipEncontrada)
        {
            string temp = "";
            int k = 0;
            // for (size_t i = 0; i < listaPCS.at(indPCAPingear).ip.size(); i++)
            // {
            //     if (listaPCS.at(indPCAPingear).ip.at(i) == '.')
            //     {
            //         arrIp[k] = temp;
            //         k++;
            //         temp="";
            //         continue;
            //     } else if(i == listaPCS.at(indPCAPingear).ip.size() -1 ){
            //         k++;
            //     }
            //     else
            //     {
            //         temp += listaPCS.at(indPCAPingear).ip.at(i);
            //     }
            //     //192.169.0.1
            // }

            vector<string> ipABuscarSeparada = split(listaPCS.at(indPCAPingear).ip, '.');
            string ipABuscarBinariaEnString = "";

            for (size_t i = 0; i < ipABuscarSeparada.size(); i++)
            {
                int n;
                istringstream(ipABuscarSeparada.at(i)) >> n;
                ipABuscarBinariaEnString += toBinary(n) + ".";
            }
            ipABuscarBinariaEnString.pop_back();

            vector<string> ipBinariaSeparada = split(ipABuscarBinariaEnString, '.');

            for (size_t i = 0; i < ipBinariaSeparada.size(); i++)
            {
                if (ipBinariaSeparada.at(i).size() != 8)
                {
                    int restantes = 8 - ipBinariaSeparada.at(i).size();
                    string temp = "";
                    for (size_t i = 0; i < restantes; i++)
                    {
                        temp += "0";
                    }
                    temp.insert(restantes, ipBinariaSeparada.at(i));
                    ipBinariaSeparada.at(i) = temp;
                }
            }

            string ipBinariaRellenadaAUsar = "";

            for (size_t i = 0; i < ipBinariaSeparada.size(); i++)
            {
                ipBinariaRellenadaAUsar += ipBinariaSeparada.at(i) + ".";
            }
            ipBinariaRellenadaAUsar.pop_back();

            vector<string> ipDelUsuarioSeparada = split(usuarioActual.ip, '.');
            string ipBinariaDelUsuario = "";

            for (size_t i = 0; i < ipDelUsuarioSeparada.size(); i++)
            {
                int ipEnEntero;
                istringstream(ipDelUsuarioSeparada.at(i)) >> ipEnEntero;
                ipBinariaDelUsuario += toBinary(ipEnEntero) + ".";
            }
            ipBinariaDelUsuario.pop_back();

            vector<string> ipDelUsuarioBinariaSeparada = split(ipBinariaDelUsuario, '.');

            for (size_t i = 0; i < ipDelUsuarioBinariaSeparada.size(); i++)
            {
                if (ipDelUsuarioBinariaSeparada.at(i).size() != 8)
                {
                    int restantes = 8 - ipDelUsuarioBinariaSeparada.at(i).size();
                    string temp = "";
                    for (size_t i = 0; i < restantes; i++)
                    {
                        temp += "0";
                    }
                    temp.insert(restantes, ipDelUsuarioBinariaSeparada.at(i));
                    ipDelUsuarioBinariaSeparada.at(i) = temp;
                }
            }

            string ipBinariaDelUsuarioRellenada = "";

            for (size_t i = 0; i < ipDelUsuarioBinariaSeparada.size(); i++)
            {
                ipBinariaDelUsuarioRellenada += ipDelUsuarioBinariaSeparada.at(i) + ".";
            }
            ipBinariaDelUsuarioRellenada.pop_back();

            vector<string> mascaraDelUsuarioSeparada = split(usuarioActual.mask, '.');
            string mascaraBinariaDelUsuario = "";

            for (size_t i = 0; i < mascaraDelUsuarioSeparada.size(); i++)
            {
                int mascaraEnEntero;
                istringstream(mascaraDelUsuarioSeparada.at(i)) >> mascaraEnEntero;
                mascaraBinariaDelUsuario += toBinary(mascaraEnEntero) + ".";
            }
            mascaraBinariaDelUsuario.pop_back();
            int contUnosEnMascara = 0;

            for (size_t i = 0; i < mascaraBinariaDelUsuario.size(); i++)
            {
                if (mascaraBinariaDelUsuario.at(i) == '1')
                {
                    contUnosEnMascara++;
                }
            }

            string ipABuscarRecortada = ipBinariaRellenadaAUsar.substr(0, contUnosEnMascara);
            string ipDelUsuarioRecortada = ipBinariaDelUsuarioRellenada.substr(0, contUnosEnMascara);

            if (ipABuscarRecortada == ipDelUsuarioRecortada)
            {
                std::cout << "Pinging to " << ipRecibida << " with 32 bytes of data: " << std::endl;
                std::cout << std::endl;
                for (int i = 0; i < 4; i++)
                {
                    std::cout << "Reply from " << ipRecibida << ": bytes=32 time=37ms TTL=46" << std::endl;
                }
                std::cout << std::endl;

                std::cout << "Ping statistics for " << ipRecibida << ": " << std::endl;
                std::cout << "      Packets: Sent = 4, Received = 4, Lost = 0 (0% Loss)" << std::endl;
            }
            else
            {
                std::cout << "Pinging to " << ipRecibida << " with 32 bytes of data: " << std::endl;
                std::cout << std::endl;
                for (int i = 0; i < 4; i++)
                {
                    std::cout << "Reply from " << ipRecibida << ": Destination host unreachable" << std::endl;
                }
                std::cout << std::endl;

                std::cout << "Ping statistics for " << ipRecibida << ": " << std::endl;
                std::cout << "      Packets: Sent = 4, Received = 4, Lost = 0 (0% Loss)" << std::endl;
            }
        }
        else
        {
            std::cout << "Pinging to " << ipRecibida << " with 32 bytes of data: " << std::endl;
            std::cout << std::endl;
            for (int i = 0; i < 4; i++)
            {
                std::cout << "Request timed out." << std::endl;
            }
            std::cout << std::endl;

            std::cout << "Ping statistics for " << ipRecibida << ": " << std::endl;
            std::cout << "      Packets: Sent = 4, Received = 0, Lost = 4 (100% Loss)" << std::endl;
        }
    };
    static void show(PC pcUsandose)
    {
        std::cout << "IP: " << pcUsandose.getIP() << std::endl;
        std::cout << "Netmask: " << pcUsandose.getNetmask() << std::endl;
    };
    string getHostname()
    {
        return hostname;
    };
};

#endif