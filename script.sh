make -C ./build #C is there to tell in which make file the make command should be executed
echo "Running the executable"
echo "delete the previous txt file"
rm file.txt
./build/RSCA_executable >> file.txt
echo "Saved in file.txt in the parent folder"
