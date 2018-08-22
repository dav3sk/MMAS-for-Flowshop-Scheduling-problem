#!/bin/bash
PROG="./ACO"
GERACOES="15000"
MAX_E=30

for ((i=10 ; i <= 120 ; i+=10)) do
    echo "=================== // ==================="
    ARQUIVO=$i

    N_FORMIGAS="5" EVAPORACAO="0.75" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do            
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.75" P_GLOBAL="0.5"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.75" P_GLOBAL="0.9"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.80" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.90" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.99" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done
    
    N_FORMIGAS="1" EVAPORACAO="0.75" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.75" P_GLOBAL="0.5"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.75" P_GLOBAL="0.9"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.80" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.90" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.99" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$ARQUIVO [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

done