import os
import json
import datetime
import re
import jinja2

USER_VERSION_FILE = 'user_version.json'
TEMPLATE_FILE = 'averUserVersion.h'
PRERELEASE = 'preRelease'
BUILD = 'build'


current_date = datetime.datetime.now()

date = current_date.strftime("%Y-%m-%d %H:%M:%S")

####################################################################
##  Compute Pre-Release Identifier
#####

def GitLabCI_PreRelease(user_version):
    # Compute Pre-release Var of GitLab CI
    res = True

    if os.getenv('CI_COMMIT_TAG'):
        # Case on tags on git kab CI
        user_version[PRERELEASE] = None
        pass
    elif os.getenv('CI_COMMIT_BRANCH'):
        user_version[PRERELEASE] = os.getenv('CI_COMMIT_BRANCH')
        # TODO : Transform for remplace char invald by '-'
    elif os.getenv('CI_MERGE_REQUEST_IID'):
        user_version[PRERELEASE] = 'PR-' + os.getenv('CI_MERGE_REQUEST_IID')
    else:
        res = False

    return res

def GitHubCI_PreRelease(user_version):
    # Compute Pre-Release Identifier on Git Hub CI
    res = False
    return res

def JenkinsCI_PreRelease(user_version):
    # Compute Pre-Release Identifier on Jenkins CI
    res = False
    return res

def User_PreRelease(user_version):
    # Build Pre Release On Local Machine
    user_version[PRERELEASE] = "{}-{}".format(os.getlogin(), current_date.year)

####################################################################
##  Compute Build Number
#####

def GitLabCI_BuildNumber(user_version):
    # Compute build Number On Gitlab CI
    res = True
    if os.getenv('CI_PIPELINE_IID'):
        user_version[BUILD] = int(os.getenv('CI_PIPELINE_IID'))
    else:
        res = False

    return res

def GitHubCI_BuildNumber(user_version):
    # Compute Build Number On GitHub CI
    return False

def JenkinsCi_BuildNumber(user_version):
    # Compute Build Number On Jenkins CI
    return False

def User_BuildNumber(user_version):
    # Compute Build Number When Built on Local Machine
    build = current_date.timetuple().tm_yday
    build = build * 24 + current_date.hour
    build = build * 60 + current_date.minute
    build = build * 60 + current_date.second

    user_version[BUILD] = build


def main():
    if os.path.isfile(USER_VERSION_FILE):
        with open(USER_VERSION_FILE, 'r') as f:
            user_version = json.load(f)
    else:
        user_version = {
            PRERELEASE: None,
            BUILD: -1
        }

    if GitHubCI_PreRelease(user_version):
        pass
    elif GitLabCI_PreRelease(user_version):
        pass
    elif JenkinsCI_PreRelease(user_version):
        pass
    else:
        User_PreRelease(user_version)

    # Normalise Pre-Release Identifier
    # Only Charater allow "[A-Za-z0-9]" | "-"
    user_version[PRERELEASE].replace('_', '-')
    user_version[PRERELEASE] = re.sub(r'\W', user_version[PRERELEASE], '-')
    if len(user_version[PRERELEASE]) >= 50:
        user_version[PRERELEASE] = user_version[PRERELEASE][:23] + '-X-' + user_version[PRERELEASE][:-23]

    if GitHubCI_BuildNumber(user_version):
        pass
    elif GitLabCI_BuildNumber(user_version):
        pass
    elif JenkinsCi_BuildNumber(user_version):
        pass
    else:
        User_BuildNumber(user_version)

    with open(USER_VERSION_FILE, 'w') as f:
        json.dump(user_version, f)

    env = jinja2.Environment(loader=jinja2.FileSystemLoader(os.path.dirname(__file__)))
    template = env.get_template(TEMPLATE_FILE)
    template.stream(user_version=user_version, date=date).dump(TEMPLATE_FILE)

    print("generate : ", TEMPLATE_FILE)
    print("version : ",  user_version)

if __name__ == '__main__':
    main()