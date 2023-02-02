#include <sys/proc.h>
#include <sys/vnode.h>

#include <libkern/libkern.h>
#include <security/mac_policy.h>

#define HOME "/Users/wurui/"

static int vnode_check_read(
    kauth_cred_t active_cred, /* SUBJECT */
    kauth_cred_t file_cred,   /* NULLOK */
    struct vnode *vp,         /* OBJECT */
    struct label *label       /* LABEL */
)
{
    int error = 0;
    int retvalue = 0;

    if (vp == NULL)
        return retvalue;

    char full_path[MAXPATHLEN + 1];
    int fplen = MAXPATHLEN;
    if (vn_getpath(vp, full_path, &fplen))
        return 0;

    char ld[] = HOME "macf_read_deny";

    if (strncmp(full_path, ld, strlen(ld)) == 0)
    {
        char procname[MAXCOMLEN + 1];
        int proclen = sizeof(procname);
        proc_selfname(procname, proclen);
        printf("EPERM %s process=%s path=%s\n", __func__, procname, full_path);
        return EPERM;
    }

    return retvalue;
}

static int
vnode_check_write(kauth_cred_t active_cred,
                  kauth_cred_t file_cred,
                  struct vnode *vp,
                  struct label *label)
{
    int error = 0;
    int retvalue = 0;

    if (vp == NULL)
        return retvalue;

    char full_path[MAXPATHLEN + 1];
    int fplen = MAXPATHLEN;
    if (vn_getpath(vp, full_path, &fplen))
        return 0;

    char ld[] = HOME "macf_write_deny";

    if (strncmp(full_path, ld, strlen(ld)) == 0)
    {
        char procname[MAXCOMLEN + 1];
        int proclen = sizeof(procname);
        proc_selfname(procname, proclen);
        printf("EPERM %s process=%s path=%s\n", __func__, procname, full_path);
        return EPERM;
    }

    return retvalue;
}

int vnode_check_exec(kauth_cred_t cred,
                     struct vnode *vp,
                     struct vnode *scriptvp,
                     struct label *vnodelabel,
                     struct label *scriptlabel,
                     struct label *execlabel,
                     struct componentname *cnp,
                     u_int *csflags,
                     void *macpolicyattr,
                     size_t macpolicyattrlen)
{
    printf("%s\n", __func__);
    char buf[PATH_MAX] = {0};
    int buflen = PATH_MAX;

    if (!vn_getpath(vp, buf, &buflen))
    {
        printf("%s: exec %s\n", __func__, buf);
        if (strcmp(buf, "/usr/bin/which") == 0)
        {
            printf("%s: DENY exec %s\n", __func__, buf);
            return EPERM;
        }
    }
    return 0;
}

static struct mac_policy_ops mac_ice_ops =
{
        // .mpo_policy_initbsd	= mac_ice_policy_initbsd,
        .mpo_vnode_check_read = vnode_check_read,
        .mpo_vnode_check_write = vnode_check_write,
        .mpo_vnode_check_exec = vnode_check_exec,
};

static mac_policy_handle_t mac_policy_handle;

static struct mac_policy_conf mac_policy_conf = {
    .mpc_name = "hello",
    .mpc_fullname = "Hello",
    .mpc_labelnames = NULL,
    .mpc_labelname_count = 0,
    .mpc_ops = &mac_ice_ops,
    .mpc_loadtime_flags = MPC_LOADTIME_FLAG_UNLOADOK,
    .mpc_field_off = NULL,
    .mpc_runtime_flags = 0};

kern_return_t kexthello_start(kmod_info_t *ki, void *d);
kern_return_t kexthello_stop(kmod_info_t *ki, void *d);

kern_return_t kexthello_start(kmod_info_t *ki, void *d)
{
    printf("%s\n", __func__);

    int status = mac_policy_register(&mac_policy_conf, &mac_policy_handle, d);
    if (status != KERN_SUCCESS)
    {
        printf("%s: failed to register MAC policy (%#x)\n", __func__, status);
        return status;
    }
    return KERN_SUCCESS;
}

kern_return_t kexthello_stop(kmod_info_t *ki, void *d)
{
    printf("%s\n", __func__);
    mac_policy_unregister(mac_policy_handle);
    return KERN_SUCCESS;
}

#include <mach/mach_types.h>

extern kern_return_t _start(kmod_info_t *ki, void *data);
extern kern_return_t _stop(kmod_info_t *ki, void *data);
// __private_extern__ kern_return_t kexthello_start(kmod_info_t *ki, void *data);
// __private_extern__ kern_return_t kexthello_stop(kmod_info_t *ki, void *data);

__attribute__((visibility("default"))) KMOD_EXPLICIT_DECL(abcd.kexthello, "1.0.0", _start, _stop) __private_extern__ kmod_start_func_t *_realmain = kexthello_start;
__private_extern__ kmod_stop_func_t *_antimain = kexthello_stop;
// __private_extern__ int _kext_apple_cc = __APPLE_CC__ ;