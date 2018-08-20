PROG="./ACO"
GERACOES="15000"
MAX_E=1

for ((i=0 ; i <= 110 ; i+=10)) do
    if [ "$i" -le 0 ]; then
        ARQUIVO=1
    else
        ARQUIVO=$i
    fi

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
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.75" P_GLOBAL="0.9"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.80" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.90" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="5" EVAPORACAO="0.99" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done
    
    N_FORMIGAS="1" EVAPORACAO="0.75" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.75" P_GLOBAL="0.5"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.75" P_GLOBAL="0.9"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.80" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.90" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

    N_FORMIGAS="1" EVAPORACAO="0.99" P_GLOBAL="0.1"
    echo
    echo ">>>> Executando ta$i [$N_FORMIGAS | $EVAPORACAO | $P_GLOBAL]"
    for (( e=0; e < MAX_E; e++ )); do    
        echo
        $PROG $N_FORMIGAS $EVAPORACAO $GERACOES $P_GLOBAL $ARQUIVO
        echo
    done

done