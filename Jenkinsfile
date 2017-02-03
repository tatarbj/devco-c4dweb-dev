node('master') {

    tokens = "${env.JOB_NAME}".tokenize('/')
    env.ORG = tokens[tokens.size()-3]
    env.REPO = tokens[tokens.size()-2]
    env.PROJECT = env.REPO.replaceAll('-reference','')

    checkout scm

    if (env.DEPLOY_SERVER) {
      stage('Deploy') {
        if( env.BRANCH_NAME != 'acceptance' ) {
          input('Proceed with deployment to ' + env.BRANCH_NAME + '?')
        }
        dir('deploy') {
          deleteDir()
        }
        checkout([
          $class: 'GitSCM', 
          branches: [[name: '*/master']], 
          doGenerateSubmoduleConfigurations: false, 
          extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: 'deploy']], 
          submoduleCfg: [], 
          userRemoteConfigs: [
            [ url:  'git@' + env.DEPLOY_SERVER + ':' + env.PROJECT + '/' + env.BRANCH_NAME + '.git']
          ]
        ])
	sh 'find web/ -type f -name .DS_Store -delete'
        sh 'find web/ -type f -name .gitignore -delete'
	sh 'rm web/install.php web/update.php web/.editorconfig'
        sh 'rsync -rpKzl --delete-after --ignore-errors --force --exclude="sites/default/files" --exclude="sites/default/settings.php" --exclude="sites/default/settings.local.php" --exclude="sites/all/modules/fpfis" --exclude=".git" --exclude=".gitignore" web/ deploy/'
	dir('deploy') {
            sh 'git checkout master'
            sh 'git add . -A'
            sh 'git commit -m"Updated ' + env.PROJECT + '@' + env.BRANCH_NAME + ' (jenkins #' + env.BUILD_ID + ')  at $(date +%Y%m%d%H%M)"'
            sh 'drush vset maintenance_mode 1'
            sh 'git push'
	    sh 'drush updb -y'
            sh 'drush fra -y'
            sh 'drush vset maintenance_mode 0'
            deleteDir()
        }
      }
    }
}
