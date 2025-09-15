#! /bin/bash

if [ "$#" != "1" ]
then
    echo "---------------------------------------------------------------------------------------------------------"
    echo "|Para executar o script, garanta que você está na raíz do seu projeto (onde seus códigos .l e .h estão)  |"
    echo "|Como único argumento do script, informe o caminho relativo onde estão os arquivos entradaX.c e saidaX_.c|"
    echo "|                         Exemplo: ./verifica_inconsistencias entradas_saidas/                           |"
    echo "---------------------------------------------------------------------------------------------------------"
    exit 2
fi

pasta_arquivos=$1

n_outs=5


for (( i=1; i<=${n_outs}; i++ ))
do
    leo_out="$pasta_arquivos/saida${i}_.txt" 
    student_out="$pasta_arquivos/saida${i}.txt"

    ./analex "${pasta_arquivos}/entrada${i}.c" > ${student_out}

    count=$(grep -n "TABELA DE SIMBOLOS" < $leo_out | tr ":TABELA DE SIMBOLOS" " ")
    line_number=$(wc $leo_out -l | tr " " "\n" | head -1)
    table_start=$(expr $line_number - $count)

    symbol_table_leo=$(tail $leo_out -n $table_start)
    line_number_leo=$line_number



    count=$(grep -n "TABELA DE SIMBOLOS" < $student_out | tr ":TABELA DE SIMBOLOS" " ")
    line_number=$(wc $student_out -l | tr " " "\n" | head -1)
    table_start=$(expr $line_number - $count)

    symbol_table_student=$(tail $student_out -n $table_start)
    line_number_student=$line_number


    if [ $line_number_student == $line_number_leo ]
    then
        if [ "$symbol_table_student" == "$symbol_table_leo" ]
        then
            echo "entrada${i}.c resultou idêntico"
        else
            echo "entrada${i}.c resultou diferente"
        fi
    else
        echo "entrada${i}.c resultou diferente"
    fi
done
