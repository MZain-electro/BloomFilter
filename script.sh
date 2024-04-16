make -C ./build #C is there to tell in which make file the make command should be executed
echo "Running the executable"
echo "delete the previous txt file"
rm output_of_mean.txt
rm file_*.txt
# Of the form CAM SIZE, Number of Sub CAMS and Range of LNREGs
# write a loop to run the executable for different values
echo "Running the executable for different values"
echo "CAM SIZE: 32, Number of Sub CAMS: 8, Range of LNREGs: 128"
for i in 2 4 8 16
do  
    echo "Running for $i"
    ./build/RSCA_executable 32 8 $((32*$i)) >> file_$i.txt
done
echo "Saved in file.txt in the parent folder"
