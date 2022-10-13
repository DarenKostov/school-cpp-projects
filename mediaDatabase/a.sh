FILE=include_all.txt
echo "" > $FILE
for file in ./*.h
do
    echo "#include \"$file\"" >> $FILE
done
for file in ./*.cpp
do
    echo "#include \"$file\"" >> $FILE
done
