#!/bin/bash

while true; do
    clear
    pids=$(pgrep minishell)

    if [ -n "$pids" ]; then
        for pid in $pids; do
            echo "🔍 Checking leaks for minishell (PID: $pid)..."
            echo "==========================================="

            output=$(leaks "$pid" 2>/dev/null)

            if [ -z "$output" ]; then
                echo "✅ No leaks detected."
            else
                # Filter out lines containing "readline"
                echo "$output" | grep -v -i "readline" | awk '
                    /leaked memory:/ {print "\033[0;31m"$0"\033[0m"}
                    /\.c:/ {print "\033[0;33m"$0"\033[0m"}
                    !/leaked memory:/ && !/\.c:/ {print $0}
                '
            fi
            echo "==========================================="
        done
    else
        echo "❌ minishell not running"
    fi

    sleep 2
done
