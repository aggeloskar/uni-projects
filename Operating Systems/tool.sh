#!/bin/bash
#Karagounis Aggelos 5532
#Leitourgika Systimata 2017-2018
#Askisi 1

#An den yparxei parametros, emfanizetai to AM
if [ $# -eq 0 ]
then
    echo "5532"
fi

#Erwtima A
#Emfanizei ola ta periexomena tou arxeiou, agnoontas ta sxolia
#Ta sxolia agnoountai me to /^[^#]/
if [ "$1" == "-f" ] && [ "$#" == 2 ]
then 
    awk '/^[^#]/ {print;}' $2
fi

#Erwtima B
#Emfanizei Onoma Eponimo ImerominiaGenisis
#Grammes sxolia agnnountai
#Me to -F '|' orizoume oti oi stiles xwrizontai me delimiter |
if [ "$1" == "-f" ] && [ "$3" == "-id" ]
then
    awk -F'|' -v id="$4" '/^[^#]/ && $1==id{print ""$3" "$2" "$5""}' $2
elif [ "$1" == "-id" ] && [ "$3" == "-f" ]
then
    awk -F'|' -v id="$2" '/^[^#]/ && $1==id{print ""$3" "$2" "$5""}' $4
fi
  
#Erwtima C
#Emfanizei ola ta firstnames
#Emfanizontai alfavitika me to sort kai diakrita me to -u
#Grammes sxolia agnoountai
if [ "$1" == "--firstnames" ] && [ "$2" == "-f" ]
then
      awk -F'|' '/^[^#]/ { print $3 }' $3 | sort -u  
elif [ "$3" == "--firstnames" ] && [ "$1" == "-f" ]
then
      awk -F'|' '/^[^#]/ { print $3 }' $2 | sort -u  
fi

#Erwtima D
#Emfanizei ola ta lastnames
#Emfanizontai alfavitika me to sort kai diakrita me to -u
#Grammes sxolia agnoountai
if [ "$1" == "--lastnames" ] && [ "$2" == "-f" ]
then
      awk -F'|' '/^[^#]/ { print $2 }' $3 | sort -u  
elif [ "$3" == "--lastnames" ] && [ "$1" == "-f" ]
then
      awk -F'|' '/^[^#]/ { print $2 }' $2 | sort -u  
fi

#Erwtima E
#Emfanizei oles tis imerominies genisis metaxy twn orion.
#Kalyptei olous tous syndiasmous seiras orismaton kai pi8ani eleipsi orismatos until h since
#Emfanizei akoma kai an den yparxei kapoio apo ta orismata --born-since kai --born-until
#Grammes sxolia agnoountai
if [ "$1" == "--born-since" ] && [ "$3" == "--born-until" ] && [ "$5" == "-f" ]
then
    awk -F '|' -v UNTIL="$4" -v SINCE="$2" '$5 <= UNTIL && $5 >= SINCE && /^[^#]/ {print}' $6
elif [ "$3" == "--born-since" ] && [ "$1" == "--born-until" ] && [ "$5" == "-f" ]
then
    awk -F '|' -v UNTIL="$2" -v SINCE="$4" '$5 <= UNTIL && $5 >= SINCE && /^[^#]/ {print}' $6
elif [ "$1" == "--born-since" ] && [ "$5" == "--born-until" ] && [ "$3" == "-f" ]
then
    awk -F '|' -v UNTIL="$6" -v SINCE="$2" '$5 <= UNTIL && $5 >= SINCE && /^[^#]/ {print}' $4
elif [ "$3" == "--born-since" ] && [ "$5" == "--born-until" ] && [ "$1" == "-f" ]
then
    awk -F '|' -v UNTIL="$6" -v SINCE="$4" '$5 <= UNTIL && $5 >= SINCE && /^[^#]/ {print}' $2
elif [ "$5" == "--born-since" ] && [ "$1" == "--born-until" ] && [ "$3" == "-f" ]
then
    awk -F '|' -v UNTIL="$2" -v SINCE="$6" '$5 <= UNTIL && $5 >= SINCE && /^[^#]/ {print}' $4
elif [ "$5" == "--born-since" ] && [ "$3" == "--born-until" ] && [ "$1" == "-f" ]
then
    awk -F '|' -v UNTIL="$4" -v SINCE="$6" '$5 <= UNTIL && $5 >= SINCE && /^[^#]/ {print}' $2
elif [ "$1" == "--born-since" ] && [ "$3" == "-f" ]
then
    awk -F "|" -v SINCE="$2" '$5 >= SINCE && /^[^#]/ {print}' $4
elif [ "$3" == "--born-since" ] && [ "$1" == "-f" ]
then
    awk -F "|" -v SINCE="$4" '$5 >= SINCE && /^[^#]/ {print}' $2
elif [ "$1" == "--born-until" ] && [ "$3" == "-f" ]
then
    awk -F "|" -v UNTIL="$2" '$5 <= UNTIL && /^[^#]/ {print}' $4
elif [ "$3" == "--born-until" ] && [ "$1" == "-f" ]
then
    awk -F "|" -v UNTIL="$4" '$5 <= UNTIL && /^[^#]/ {print}' $2
fi

#Erwtima F
#Emfanizei alfavitika tous browsers kai poses fores emfanizontai 
#Me tin xrisi tou END, emfanizontai ta apotelesmata tou END block meta tin ektelesi oloklirou tou awk kwdika
#Xrisimopoiw for loop i opoia metraei ton ari8mo pou emfanizetai ka8e browser b
#Emfanizontai alfavitika me to sort
#Grammes sxolia agnoountai
if [ "$1" == "--browsers" ] && [ "$2" == "-f" ]
then
    awk -F '|' '/^[^#]/ { b[$8]++} END { for(i in b) print i, b[i]  }' $3 | sort -u
fi

if [ "$3" == "--browsers" ] && [ "$1" == "-f" ]
then
    awk -F '|' '/^[^#]/ { b[$8]++} END { for(i in b) print i, b[i]  }' $2 | sort -u
fi

#Erwtima G
#Kanei allagi tin stili tis metavlitis col me oti yparxei stin metavliti allagi an to myid yparxei sto arxeio isodou
#I allagi ginetai mono an col meta3y 2 kai 8 
#An den vre8ei to id den pragmatopoieitai kamia allagi
#Epeidi me to awk den boroume na grapsoume tautoxrona sto arxeio apo to opeio diavazoume, grafoume prwta se ena prosorino arxeio tempfile.tmp kai meta sto arxeio eisodou
#I allagi ginetai sto arxeio eisodou.
if [ "$1" == "-f" ] && [ "$3" == "--edit" ]
then
awk -v FS='|' -v OFS='|' -v myid="$4" -v col="$5" -v allagi="$6" '{ if($1 == myid && col>1 && col<9) { $col=allagi; } print}' $2 > tempfile.tmp && mv tempfile.tmp $2
elif [ "$5" == "-f" ] && [ "$1" == "--edit" ]
then
awk -v FS='|' -v OFS='|' -v myid="$2" -v col="$3" -v allagi="$4" '{ if($1 == myid && col>1 && col<9) { $col=allagi; } print}' $6 > tempfile.tmp && mv tempfile.tmp $6
fi