clean:
	find . -perm +111 -type f -depth 1|xargs rm
