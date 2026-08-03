#! /bin/bash
#
rev_new=$(git rev-parse --short=7 HEAD)

rev_old=$(cat ./src/gitrev.c 2>/dev/null | tr -d '\n' | awk -F"\"" '{print $2}' | awk -F"\"" '{print $1}')


if [ "$rev_new" != "$rev_old" ] || [ ! -f ./src/gitrev.c ]; then

	if [ -n "$rev_new" ]; then
		echo "Changed Rev $rev_old to $rev_new" >&2
	fi

    cat <<EOF > ./src/gitrev.c
#define GIT_REV "$rev_new"

const char *GetRev()
{
	return GIT_REV;
}

fi

echo $rev_new
