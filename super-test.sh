#!/bin/bash

source /lib/gentoo/functions.sh

while getopts 'r:j:l:' opt; do
    case ${opt} in
        r)
            einfo "testing on repo at ${OPTARG}"
            repo=${OPTARG}
            ;;
    esac
done

if [[ -z ${repo} ]]; then
    eerror "no repo was specified"
    exit 1
fi

git -C ${repo} reset --hard origin/master || exit $?

commits=($(git -C ${repo} log --format='%H' | shuf))

_run() {
    local commit=${1}

    git -C ${repo} checkout ${commit} . || exit $?

    meson test -v --test-args ${repo} '*repo*' -C build
}

export -f _run

for commit in ${commits[@]}; do
    _run ${commit}
done

