 for i in {01..31};
    do diff tests/$i.a tests/$i.o -w;
 done