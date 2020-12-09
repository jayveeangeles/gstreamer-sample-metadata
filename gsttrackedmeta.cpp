
#include "gsttrackedmeta.h"

GType
gst_trackedmetas_api_get_type (void)
{
  static GType type;

  if (g_once_init_enter (&type)) {
    const gchar *tags[] = { NULL };
    GType _type =
      gst_meta_api_type_register ("GstTrackedMetasAPI", tags);
    g_once_init_leave (&type, _type);
  }

  return type;
}

static gboolean
gst_trackedmetas_init (GstMeta * meta, gpointer params,
  GstBuffer * buffer)
{
  return TRUE;
}

static gboolean
gst_trackedmetas_transform (GstBuffer * dest_buf, GstMeta * src_meta,
  GstBuffer * src_buf, GQuark type, gpointer data)
{
  GstTrackedMetas *src_dets = (GstTrackedMetas *) src_meta;
  GstTrackedMetas *dest_dets =
    GST_TRACKEDMETAS_ADD (dest_buf);

  // copy tracked data if there are any
  dest_dets->tracked_count = src_dets->tracked_count;
  for (guint i = 0; i < dest_dets->tracked_count; i++) {
    dest_dets->tracked[i] = src_dets->tracked[i];
  }

  return TRUE;
}

static void
gst_trackedmetas_free (GstMeta * meta, GstBuffer * buffer)
{
}

const GstMetaInfo *
gst_trackedmetas_get_info (void)
{
  static const GstMetaInfo *meta_info = NULL;

  if (g_once_init_enter (&meta_info)) {
    const GstMetaInfo *meta =
      gst_meta_register (gst_trackedmetas_api_get_type (),
      "GstTrackedMetas",
      sizeof (GstTrackedMetas),
      gst_trackedmetas_init,
      gst_trackedmetas_free,
      gst_trackedmetas_transform);
    g_once_init_leave (&meta_info, meta);
  }

  return meta_info;
}
// Only for Python : return GstBufferInfo instead of GstBufferInfoMeta
// To avoid GstMeta (C) map to Gst.Meta (Python)
GstTrackedMeta* gst_trackedmetas_get_info_tracked(GstBuffer* buffer)
{   
  GstTrackedMetas *meta = \
    (GstTrackedMetas *) gst_buffer_get_meta (buffer, gst_trackedmetas_api_get_type());

  if (meta == NULL)
    return NULL;
  else
    return meta->tracked;   
}

guint gst_trackedmetas_get_info_tracked_count(GstBuffer* buffer)
{   
  GstTrackedMetas *meta = \
    (GstTrackedMetas *) gst_buffer_get_meta (buffer, gst_trackedmetas_api_get_type());

  if (meta == NULL)
    return 0;
  else
    return meta->tracked_count;   
}