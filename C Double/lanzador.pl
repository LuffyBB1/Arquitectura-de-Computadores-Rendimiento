#!/usr/bin/perl

=begin
Fecha: 26-08-2022
Autor: Brayan Bernal
Tema: Automatización de bateria de expermientos
Materia: Parallel and Dsitributed computing
Requerimientos:
	-Vector de Becnhmark <ejecutables>
	-Vector de cargas
	-N: repeticiones
	-Iterar por ejecutables * cargas * repeticiones
	
=cut

 #Se crea el vector de ejecutables
 @Ejecutables = ("mm_main_double","mm_main_double_rmd");
 #Se crea el vector de cargas
 @Cargas = ("10","30","50", "70", "100", "300", "500","700", "1000",);
 $N=10;
 
 foreach $exes (@Ejecutables){
 	foreach $carga (@Cargas){
 		#Se crea un fichero
 		$file = "Soluciones/"."$exes"."_$carga".".csv";
 		for ($i=0;$i<$N;$i++){
 			system("./$exes $carga>> $file");
 			}
 		close($file);
 		}
 	}

