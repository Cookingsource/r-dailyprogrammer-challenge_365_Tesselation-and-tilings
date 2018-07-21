#echo bash_source="${BASH_SOURCE}"
#echo dirname="$(dirname "${BASH_SOURCE}")"
parent_path=$( cd "$(dirname "${BASH_SOURCE}")"; pwd -P);
#echo $parent_path

pushd $parent_path >/dev/null
mkdir -p ../build
clang tesselator.cpp -o ../build/tesselator.out
popd >/dev/null