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
proyectoActual=$(pwd);
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
    echo -e "\t\t\t g.  Ver Cantidad de Memoria Principal";
    echo -e "\t\t\t h.  Ver Placa de Video";
    echo -e "\t\t\t i.  Ver Idioma Teclado";
    echo -e "\t\t\t j.  Comprobar programa instalado";
    echo -e "\t\t\t k.  Crear ususario";
    echo -e "\t\t\t l.  Ver actividad de usuarios";
    echo -e "\t\t\t m.  Interactuando con otros sistemas (Ej 2)";
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
    #echo $1;
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
    echo "ls-l";
    decidir "ls -l";
}

b_funcion () {
    imprimir_encabezado "\tOpción b.  Kernel";
    echo "uname -r";
   	decidir "uname -r";
}

c_funcion () {
    imprimir_encabezado "\tOpción c.  Arquitectura";
    echo "uname -m";
    decidir "uname -m"
}

d_funcion () {
    imprimir_encabezado "\tOpción d.  CPU";
    echo "cat /proc/cpuinfo | grep 'model name'";
    decidir "cat /proc/cpuinfo | grep 'model name'"
}

e_funcion () {
    imprimir_encabezado "\tOpción e.  Interrupciones";
    echo "head -n 10 /proc/interrupts";
    decidir "head -n 10 /proc/interrupts"
}

f_funcion () {
    imprimir_encabezado "\tOpción f.  Swap";
    echo "cat /proc/swaps";
    decidir "cat /proc/swaps"
}

g_funcion () {
    imprimir_encabezado "\tOpción g.  Cantidad de Memoria";
    echo "free -h";
    decidir "free -h"
}

h_funcion () {
    imprimir_encabezado "\tOpción h.  Placa de Video";
    echo "lspci |grep VGA";
    decidir "lspci |grep VGA"
}

i_funcion () {
    imprimir_encabezado "\tOpción i.  Idioma Teclado";
    echo "localectl status";
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
    imprimir_encabezado "\tOpción k.  Crear usuario";
    echo "Ingrese un nombre de usuario:"
    read nombreUsuario
    echo "sudo useradd -g sudo $nombreUsuario"
    decidir "sudo useradd -g sudo $nombreUsuario"
    echo "sudo passwd $nombreUsuario"
    decidir "sudo passwd $nombreUsuario"
    echo "sudo login $nombreUsuario"
    decidir "sudo login $nombreUsuario"

}
l_funcion () {
    imprimir_encabezado "\tOpción l.  Ver actividad de usuario";
    echo "Ingrese usuario:"
    read usuario
    cat /var/log/auth.log | grep $usuario > actividad_$usuario.txt
    gedit actividad_$usuario.txt&

}
m_funcion () {
    imprimir_encabezado "\tOpción m.  Ejecutar comandos";
    let nrolinea=0;
    FILENAME="comandos.txt"
    exec {FD}<${FILENAME}
    while read -r -u ${FD} linea;
    do
        firstChar="${linea:0:1}";
        if [[ $firstChar =~ [A-Za-z] ]]; then
            echo "-----------------------------------------"
            echo -e "$USER@$HOSTNAME:$proyectoActual\n"
            let nrolinea++
            echo "linea $nrolinea: $linea"
            decidir "$linea"
        else
            echo "$linea"
        fi
    done {FD}< comandos.txt
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
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done


