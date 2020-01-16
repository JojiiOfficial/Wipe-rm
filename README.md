# Wipe-rm
Remove your files completely from your harddisk by overwriting it with zeros before deleting it.

# Compiling
`gcc -o wrm main.c`

# Installing
`sudo cp wrm /bin/wrm`

You can also add an alias to `rm` if you want to use wrm instead of the default `rm`. To add the alias you need to run one of the following lines.<br><br> If you are using <b>BASH</b><br>
`echo 'alias rm="wrm"' >> ~/.bashrc`<br><br>
If you're using <b>ZSH</b> run this command<br>
`echo 'alias rm="wrm"' >> ~/.zshrc`<br>

# Usage
The usage is very simple and similar to `rm`<br>
`wrm [-rfvqz] [Files...]` <br><br>
`-r` recursive delete (delete folders)<br>
`-f` force delete (ignore errors)<br>
`-v` verbose (view more output)<br>
`-q` quiet (show almost nothing)<br>
`-z` zero only (only zeroing the files, don't delete them)<br>


# Security
I made this for educational purposes. I have no responsibilities if your files aren't 100% deleted or any damage will be applied on your computer! In addition this is a program to <b>DELETE FILES</b>. So watch out what you're doing with it!
