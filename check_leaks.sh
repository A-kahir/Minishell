while true; do
	clear
	pid=$(pgrep minishell)
	if [ -n "$pid" ]; then
		echo "Checking leaks for minishell (PID: $pid)"
		leaks $pid
	else
		echo "minishell not running"
	fi
	sleep 2
done

