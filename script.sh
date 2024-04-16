make -C ./build #C is there to tell in which make file the make command should be executed
echo "Running the executable"
echo "delete the previous txt file"
rm file.txt
# Of the form CAM SIZE, Number of Sub CAMS and Range of LNREGs
./build/RSCA_executable 32 8 128 >> file.txt
echo "Saved in file.txt in the parent folder"
