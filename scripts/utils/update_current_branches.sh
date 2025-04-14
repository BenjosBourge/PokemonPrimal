#!/bin/bash

# Check the number of arguments
if [ "$#" -eq 0 ]; then
    target_branch="dev"
elif [ "$#" -eq 1 ]; then
    target_branch="$1"
else
    echo "Error: The script takes at most 1 argument (target branch name)."
    exit 1
fi

# Get the name of the current branch
current_branch=$(git symbolic-ref --short HEAD)

# Check if the current branch is "dev"
if [ "$current_branch" == "dev" ]; then
    echo "Error: You are currently on the 'dev' branch. Merging 'dev' into itself is not recommended."
    exit 1
fi

# Ask the user if they want to continue with the merge
read -p "Do you want to merge '$target_branch' into '$current_branch'? (y/n) " answer

# Check the user's response
if [[ "$answer" =~ ^[Yy](es)?$ ]]; then
    # Update the target branch
    git checkout "$target_branch"

    # Attempt to pull changes from the remote
    pull_output=$(git pull origin "$target_branch" 2>&1)

    # Check the return status of git pull
    if [ $? -eq 0 ]; then
        # Pull was successful
        echo "Git pull successful."
    else
        # Pull encountered an error
        echo "Error during git pull:"
        echo "$pull_output"
        exit 1
    fi

    # Return to the original branch
    git checkout "$current_branch"

    # Merge the target branch into the current branch
    git merge "$target_branch"

    # Check for merge conflicts
    if [ $? -eq 0 ]; then
        # No conflicts, continue with the update
        # Update the remote repository
        git push origin "$current_branch"
        echo "The merge of branch '$target_branch' into '$current_branch' was successful."
    else
        # Conflicts detected
        echo "Conflicts are present. Please resolve them manually and execute 'git merge --continue' before rerunning this script."
        exit 1
    fi
else
    echo "Operation canceled by the user."
fi
