#!/usr/bin/perl

#VARIABLE QUE REPRESENTA LA CANTIDAD DE REPETICIONES

$N =10;
#SE CREA UN VECTOR DE EJECUTABLES

@Ejecutables = ("MM1cOMP");

@Cores = ("8");

@Dimension = ("10","30","50","70","100","300","500","700","1000");

foreach $exe (@Ejecutables){
	foreach $core (@Cores){
		foreach $size (@Dimension){
			$File = "Soluciones/"."$exe"."-$core"."-$size".".csv";

			#print("$File\n");
			for ($i=0; $i<$N;$i++){
				system "./$exe $size $core >> $File";

				#print("$PATH/$exe $size  \n");
			}
			close ($File);
		}
	}
}
exit(0);


