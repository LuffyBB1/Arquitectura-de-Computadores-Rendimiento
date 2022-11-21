#!/usr/bin/perl

#VARIABLE QUE REPRESENTA LA CANTIDAD DE REPETICIONES

$N =10;
#SE CREA UN VECTOR DE EJECUTABLES

@Ejecutables = ("ejecutable_bench03");

@Dimension = ("10","30","50","70","100","300","500","700","1000");

foreach $exe (@Ejecutables){
	foreach $size (@Dimension){
		$File = "Soluciones/"."$exe"."-$size".".csv";

		#print("$File\n");
		for ($i=0; $i<$N;$i++){
			system "./$exe $size >> $File";

		}
		close ($File);
	}
}
exit(0);
