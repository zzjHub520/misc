#!/bin/bash

basepath=/home/zzj/workspaces/experiment/java
startupScriptName=aahhh


cat > ${basepath}/${startupScriptName}.sh <<EOF
#!/bin/bash

nohup java -jar ${basepath}/autostart-test-0.0.1-SNAPSHOT.jar > ${basepath}/log.log 2>&1 &

EOF

mv ${basepath}/${startupScriptName}.sh /etc/profile.d/