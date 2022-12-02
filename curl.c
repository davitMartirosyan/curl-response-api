#include <curl/curl.h>
#include <unistd.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/libft.h"

int main(void)
{
	const char *data;
	const char *line;
	const char *datafile;
	int response_data;
	CURL *curl;
	CURLcode response;
	pid_t pid;

	datafile = "data.json";

	pid = fork();
	if(pid == 0)
	{
		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.boredapi.com/api/activity");
		response_data = open(datafile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(response_data, STDOUT_FILENO);
		response = curl_easy_perform(curl);
		close(response_data);
		exit(1);
	}
	waitpid(-1, 0, 0);

	data = NULL;
	response_data = open(datafile, O_RDONLY);
	line = get_next_line(response_data);
	while(line)
	{
		data = ft_strjoin(data, line);
		line = get_next_line(response_data);
	}
	char **sp = ft_split(data, ',');
	int i = -1;
	while(sp[++i])
		printf("%s\n", sp[i]);
}