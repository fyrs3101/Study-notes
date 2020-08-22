# Git 基本命令

## 创建版本库

1.  **创建一个空目录**

    ```shell
    $ mkdir learngit
    $ cd learngit
    ```

2.  **通过 `git init` 将此目录变成 git 可以管理的仓库**

    ```shell
    $ git init
    ```

    此时会多了一个 `.git` 的目录，不一定必须要在空目录下创建 git 仓库



## 将文件添加到 git 仓库

1.  `git add`

    ```shell
    $ git add filename
    ```

2.  `git commit`

    ```shell
    $ git commit -m "add filename"
    ```

    `-m` 后面输入本次提交说明，可以是任意内容



## 其他命令

-    `git status`

    输出仓库当前的状态

-   `git config`

    可以在系统、用户、项目三个级别进行配置，每一个级别会覆盖上一个级别的配置。

    -   系统

        存储在 `/etc/gitconfig` 文件中，执行 `git config` 时需要带上 `--system` 选项

    -   用户

        存储在 `~/.gitconfig` 或 `~/.config/git/config` 中，只针对当前用户。需要带上

         `--global` 选项

    -   项目

        当前使用仓库的 Git 目录中的 `.git/config` 中，针对该仓库。带上 `--local`

    **查看所有配置以及他们所在的文件**

    ```bash
    $ git config --list --show-origin
    ```

    **配置用户信息**

    ```bash
    $ git config --global user.name "luoxin"
    $ git config --global user.email luoxin9712@163.com
    ```

    **检查 git 某一项配置**

    ```bash
    $ git config user.name
    luoixn
    ```

-   `git log`

    用于查看提交历史

    | 选项          | 说明                                                         |
    | ------------- | ------------------------------------------------------------ |
    | -p            | 按补丁格式显示每个提交引入的差异。                           |
    | --stat        | 显示每次提交的文件修改统计信息。                             |
    | --shortstat   | 只显示 --stat 中最后的行数修改添加移除统计。                 |
    | --name-only   | 仅在提交信息后显示已修改的文件清单。                         |
    | --name-status | 显示新增、修改、删除的文件清单。                             |
    | --graph       | 在日志旁以 ASCII 图形显示分支与合并历史。                    |
    | --oneline     | `--pretty=oneline --abbrev-commit` 合用的简写                |
    | --pretty      | 使用其他格式显示历史提交信息。可用的选项包括 oneline和 format（用来定义自己的格式）。 |

    ```bash
    $ git log --pretty=format:"%h - %an, %ar : %s"
    ```

    

    限制输出长度

    | 选项                  | 说明                                       |
    | --------------------- | ------------------------------------------ |
    | `-<n>`                | 仅显示最近的 n 条提交。                    |
    | `--since`, `--after`  | 仅显示指定时间之后的提交。                 |
    | `--until`, `--before` | 仅显示指定时间之前的提交。                 |
    | `--author`            | 仅显示作者匹配指定字符串的提交。           |
    | `--grep`              | 仅显示提交说明中包含指定字符串的提交。     |
    | `-S`                  | 仅显示添加或删除内容匹配指定字符串的提交。 |

    对时间进行限制时，格式较为宽松

    ```bash
    $ git log --since=2weeks
    $ git log --since="10 hours ago"
    $ git log --since="2020-08-01 22:00"
    ```

-   

