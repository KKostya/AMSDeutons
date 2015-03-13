likelihood: QualityLikelihoodTrain.cpp
	g++ -o likelihood  QualityLikelihoodTrain.cpp `root-config --cflags --libs` -lTMVA

bdt: TrainBDT.cpp
	g++ -o bdt  TrainBDT.cpp `root-config --cflags --libs` -lTMVA

plots.pdf:
	rm -rf plots
	root -l -b -q "plottingScripts/variables.C(\"QualityLikelihood.root\")"
	root -l -b -q "plottingScripts/variables.C(\"QualityLikelihood.root\",\"InputVariables_Deco\", \"Decorellated Variables\")"
	root -l -b -q "plottingScripts/variables.C(\"QualityLikelihood.root\",\"InputVariables_PCA\", \"Prinipal components\")"
	root -l -b -q "plottingScripts/correlations.C(\"QualityLikelihood.root\")"
	root -l -b -q "plottingScripts/mvas.C(\"QualityLikelihood.root\")"
	root -l -b -q "plottingScripts/likelihoodrefs.C(\"QualityLikelihood.root\")"
	root -l -b -q "plottingScripts/efficiencies.C(\"QualityLikelihood.root\")"
	gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=plots.pdf `ls -hrt plots/*`
		

plotsBDT.pdf:
	rm -rf plots
	root -l -b -q "plottingScripts/variables.C(\"QualityBDT.root\")"
	root -l -b -q "plottingScripts/variables.C(\"QualityBDT.root\",\"InputVariables_Deco\", \"Decorellated Variables\")"
	root -l -b -q "plottingScripts/variables.C(\"QualityBDT.root\",\"InputVariables_PCA\", \"Prinipal components\")"
	root -l -b -q "plottingScripts/correlations.C(\"QualityBDT.root\")"
	root -l -b -q "plottingScripts/mvas.C(\"QualityBDT.root\")"
	root -l -b -q "plottingScripts/likelihoodrefs.C(\"QualityBDT.root\")"
	root -l -b -q "plottingScripts/efficiencies.C(\"QualityBDT.root\")"
	gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=plotsBDT.pdf `ls -hrt plots/*`
		





