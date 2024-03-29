#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include "IPrintPlugin.h"
#include "dlfcn.h"

CPluginController::CPluginController(void)
{
}

CPluginController::~CPluginController(void)
{
}

bool CPluginController::InitializeController(void)
{
	std::vector<std::string> vstrPluginNames;

	CPluginEnumerator enumerator;
	if (!enumerator.GetPluginNames(vstrPluginNames))
		return false;

	for (unsigned int i = 0; i < vstrPluginNames.size(); i++)
	{
		typedef int (*PLUGIN_CREATE)(IPrintPlugin **);
		PLUGIN_CREATE CreateProc;

		IPrintPlugin *pPlugin = NULL;

		void *hinstLib = dlopen(vstrPluginNames[i].c_str(), RTLD_LAZY);

		if (hinstLib != NULL)
		{
			m_vhForPlugin.push_back(hinstLib);

			CreateProc = (PLUGIN_CREATE)dlsym(hinstLib, "CreateObj");

			if (NULL != CreateProc)
			{
				(CreateProc)(&pPlugin);

				if (pPlugin != NULL)
				{
					m_vpPlugin.push_back(pPlugin);
				}
			}
		}
	}

	return true;
}

bool CPluginController::ProcessRequest(int FunctionID)
{
	for (unsigned int i = 0; i < m_vpPlugin.size(); i++)
	{
		if (m_vpPlugin[i]->GetID() == FunctionID)
		{
			m_vpPlugin[i]->Print();
			break;
		}
	}

	return true;
}

bool CPluginController::ProcessHelp(void)
{
	std::vector<std::string> vstrPluginNames;

	CPluginEnumerator enumerator;
	if (!enumerator.GetPluginNames(vstrPluginNames))
		return false;

	for (unsigned int i = 0; i < vstrPluginNames.size(); i++)
	{
		typedef int (*PLUGIN_CREATE)(IPrintPlugin **);
		PLUGIN_CREATE CreateProc;

		IPrintPlugin *pPlugin = NULL;

		void *hinstLib = dlopen(vstrPluginNames[i].c_str(), RTLD_LAZY);

		if (hinstLib != NULL)
		{
			CreateProc = (PLUGIN_CREATE)dlsym(hinstLib, "CreateObj");

			if (NULL != CreateProc)
			{
				(CreateProc)(&pPlugin);

				if (pPlugin != NULL)
				{
					pPlugin->Help();
				}
			}

			dlclose(hinstLib);
		}
	}

	return true;
}

bool CPluginController::UninitializeController()
{
	for (unsigned int i = 0; i < m_vhForPlugin.size(); i++)
	{
		dlclose(m_vhForPlugin[i]);
	}

	return true;
}
