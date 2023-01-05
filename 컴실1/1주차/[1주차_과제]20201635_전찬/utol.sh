echo "Working directory":
read dir_name
first_dir="$(pwd)"


if [ $dir_name ]; then
	cd $dir_name
	if [ $? != 0 ]; then
		exit 10
	fi
fi

for i in *
do
	newname=`echo $i | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
	mv "$i" "$newname"
done

cd $first_dir
