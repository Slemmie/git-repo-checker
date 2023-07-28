#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool check_git_status(const fs::path& dir) {
	bool result = false;

	std::string git_root = dir.parent_path().string();

	std::string cmd = "cd " + git_root + " && ";

	std::string status_cmd = cmd + "git status --porcelain | grep . > /dev/null 2>&1";
	if (!std::system(status_cmd.c_str())) {
		std::cout << "   \033[1;97mrepository '" << git_root << "' has uncomitted/untracked files\033[0m" << std::endl;
		result = true;
	}

	std::string push_cmd = cmd + "git log @{u}.. | grep . > /dev/null 2>&1";
	if (!std::system(push_cmd.c_str())) {
		std::cout << "   \033[1;97mrepository '" << git_root << "' has unpushed commits\033[0m" << std::endl;
		result = true;
	}

	return result;
}

size_t check_git_status_recursive(const fs::path& root) {
	size_t found = 0;

	for (auto& entry : fs::recursive_directory_iterator(root)) {
		if (entry.is_directory() && entry.path().filename() == ".git") {
			found += check_git_status(entry.path());
		}
	}

	return found;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "usage: " << argv[0] << " <path>" << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		fs::path path = argv[i];

		std::cout << (i > 1 ? "\n" : "") << "\033[37mchecking '" << path.string() << "':\033[0m" << std::endl;

		if (!fs::is_directory(path)) {
			std::cout << "\033[33mwarning: '" << path << "' is not a directory, ignoring\033[0m" << std::endl;
			continue;
		}

		size_t found = check_git_status_recursive(path);

		if (found) {
			std::cout << "\033[37m> found " << found << " repositories with uncomitted/untracked files or unpushed commits\033[0m" << std::endl;
		} else {
			std::cout << "\033[37m> no repositories with uncomitted/untracked files or unpushed commits found\033[0m" << std::endl;
		}
	}

	return 0;
}
