#!/bin/bash
#------------------------------------------------------
# PALETA DE COLORES
#------------------------------------------------------
#setaf para color de letras/setab: color de fondo
    red=`tput setaf 1`;
    green=`tput setaf 2`;
    blue=`tput setaf 4`;
    bg_blue=`tput setab 4`;
    reset=`tput sgr0`;
    bold=`tput setaf bold`;
#------------------------------------------------------
# VARIABLES GLOBALES
#------------------------------------------------------
proyectoActual="/home/sor1";
proyectos="/home/sor1/Documents/repo_GitLab/repos.txt";

#------------------------------------------------------
# DISPLAY MENU
#------------------------------------------------------
imprimir_menu () {
       imprimir_encabezado "\t  S  U  P  E  R  -  M  E  N U ";

    echo -e "\t\t El proyecto actual es:";
    echo -e "\t\t $proyectoActual";

    echo -e "\t\t";
    echo -e "\t\t Opciones:";
    echo "";
    echo -e "\t\t\t a.  Ver contenido de carpeta";
    echo -e "\t\t\t b.  Ver Kernel";
    echo -e "\t\t\t c.  Ver Arquitectura PC";
    echo -e "\t\t\t d.  Identificar CPU";
    echo -e "\t\t\t e.  Ver Interrupciones";
    echo -e "\t\t\t f.  Ver Swap";
    echo -e "\t\t\t g.  Ver Cnatidad de Moemoria Principal";
    echo -e "\t\t\t h.  Ver Placa de Video";
    echo -e "\t\t\t i.  Ver Idioma Teclado";
    echo -e "\t\t\t j.  Comprobar programa instalado";
    echo -e "\t\t\t k.  Crear ususario sor1";
    echo -e "\t\t\t l.  ....";
    echo -e "\t\t\t m.  Interactuando con otros sistemas";
    echo -e "\t\t\t n.  ....";
    echo -e "\t\t\t q.  Salir";
    echo "";
    echo -e "Escriba la opción y presione ENTER";
}

#------------------------------------------------------
# FUNCTIONES AUXILIARES
#------------------------------------------------------

imprimir_encabezado () {
    clear;
    #Se le agrega formato a la fecha que muestra
    #Se agrega variable $USER para ver que usuario está ejecutando
    echo -e "`date +"%d-%m-%Y %T" `\t\t\t\t\t USERNAME:$USER";
    echo "";
    #Se agregan colores a encabezado
    echo -e "\t\t ${bg_blue} ${red} ${bold}--------------------------------------\t${reset}";
    echo -e "\t\t ${bold}${bg_blue}${red}$1\t\t${reset}";
    echo -e "\t\t ${bg_blue}${red} ${bold} --------------------------------------\t${reset}";
    echo "";
}

esperar () {
    echo "";
    echo -e "Presione enter para continuar";
    read ENTER ;
}

malaEleccion () {
    echo -e "Selección Inválida ..." ;
}

decidir () {
    echo $1;
    while true; do
        echo "desea ejecutar? (s/n)";
            read respuesta;
            case $respuesta in
                   [Nn]* ) break;;
                   [Ss]* ) eval $1
                break;;
                * ) echo "Por favor tipear S/s ó N/n.";;
            esac
    done
}

#------------------------------------------------------
# FUNCTIONES del MENU
#------------------------------------------------------
a_funcion () {
    imprimir_encabezado "\tOpción a.  Ver estado del proyecto";
    decidir "ls -l";
}

b_funcion () {
    imprimir_encabezado "\tOpción b.  Kernel";
   	decidir "uname -r";
}

c_funcion () {
    imprimir_encabezado "\tOpción c.  Arquitectura";
    decidir "uname -m"
}

d_funcion () {
    imprimir_encabezado "\tOpción d.  CPU";
    decidir "cat /proc/cpuinfo | grep 'model name'"
}

e_funcion () {
    imprimir_encabezado "\tOpción e.  Interrupciones";
    decidir "head -n 10 /proc/interrupts"
}

f_funcion () {
    imprimir_encabezado "\tOpción f.  Swap";
    decidir "cat /proc/swaps"
}

g_funcion () {
    imprimir_encabezado "\tOpción g.  Cantidad de Memoria";
    decidir "free -h"
}

h_funcion () {
    imprimir_encabezado "\tOpción h.  Placa de Video";
    decidir "lspci |grep VGA"
}

i_funcion () {
    imprimir_encabezado "\tOpción i.  Idioma Teclado";
    decidir "localectl status"
}
j_funcion () {
    imprimir_encabezado "\tOpción j.  Comprobar programa instalado";
    echo -e "Escriba nombre del programa"
            read programa
            echo "";
            if dpkg -l | grep $programa; then
                echo "";
                echo "El programa $programa se encuentra instalado"
            else
                echo "";
                echo "El programa $programa no se encuentra instalado"
            fi
}
k_funcion () {
    imprimir_encabezado "\tOpción k.  Crear usuario sor1";

    sudo useradd -g sudo sor1
    sudo passwd sor1
    sudo login sor1

}
l_funcion () {
    imprimir_encabezado "\tOpción l.  ....";
    decidir ""
}
m_funcion () {
    imprimir_encabezado "\tOpción m.  Ejecutar comandos";
    let nrolinea=0;
    while read linea; do
        firstChar="${linea:0:1}";
        if [ "$firstChar" = "#" ]; then
            echo "$linea"
        elif [ "$firstChar" = "" ]; then
            echo ""
        else
            echo "---------------------------------------"
            echo -e "user@maquina: directorio\n"
            let nrolinea++
            echo "linea $nrolinea: $linea"   
            #decidir "$linea"
        fi
    done < comandos.txt
}
n_funcion () {
    imprimir_encabezado "\tOpción n.  ....";
    decidir ""
}

#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;

    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        f|F) f_funcion;;
        g|G) g_funcion;;
        h|H) h_funcion;;
        i|I) i_funcion;;
        j|J) j_funcion;;
        k|K) k_funcion;;
        l|L) l_funcion;;
        m|M) m_funcion;;
        n|N) n_funcion;;
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done


