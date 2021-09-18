#cat camp2.sh

#!/bin/bash
bot1=0
bot2=0
for (( i=0; i<100; i++ )); do 
    vencedor=$(node lib/buraco.js -silent bin/botenildson bin/botbase|grep NOK|sed -e 's/\(.*\.\)\(bot.*\)\(\ .*\)/\2/g');    
    echo $vencedor ganhou!
    if [[ "${vencedor}" =~ "p1.botenildson" ]]; then ((bot1++)); fi
    if [[ "${vencedor}" =~ "p2.botbase" ]]; then ((bot2++)); fi
    echo bot1 $bot1 X $bot2 bot2;
done