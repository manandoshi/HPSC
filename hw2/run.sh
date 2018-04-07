cd mpi
bash main_script.sh
cd ../cuda/
bash conv.sh
cd ..
python report.py
pdflatex report.tex
