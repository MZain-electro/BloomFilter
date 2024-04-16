make -C ./build #C is there to tell in which make file the make command should be executed
echo "Running the executable"
echo "delete the previous txt file"
rm output_of_mean.txt
rm file_*.txt
cam_size=64
num_sub_cams=8
# Of the form CAM SIZE, Number of Sub CAMS and Range of LNREGs
# write a loop to run the executable for different values
echo "Running the executable for different values"
for i in 2 4 8 16 32 64 128
do  
    echo "Running for $i"
    ./build/RSCA_executable $cam_size $num_sub_cams $(($cam_size*$i)) >> file_$i.txt
done
echo "Saved in file.txt in the parent folder"
