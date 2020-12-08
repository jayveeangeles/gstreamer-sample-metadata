
#include "gstdetectionsmeta.h"

GType
gst_detectionmetas_api_get_type (void)
{
  static GType type;

  if (g_once_init_enter (&type)) {
    const gchar *tags[] = { NULL };
    GType _type =
      gst_meta_api_type_register ("GstDetectionMetasAPI", tags);
    g_once_init_leave (&type, _type);
  }

  return type;
}

static gboolean
gst_detectionmetas_init (GstMeta * meta, gpointer params,
  GstBuffer * buffer)
{
  return TRUE;
}

static gboolean
gst_detectionmetas_transform (GstBuffer * dest_buf, GstMeta * src_meta,
  GstBuffer * src_buf, GQuark type, gpointer data)
{
  GstDetectionMetas *src_dets = (GstDetectionMetas *) src_meta;
  GstDetectionMetas *dest_dets =
    GST_DETECTIONMETAS_ADD (dest_buf);

  // copy detections if there are any
  dest_dets->detections_count = src_dets->detections_count;
  for (guint i = 0; i < dest_dets->detections_count; i++) {
    dest_dets->detections[i] = src_dets->detections[i];
  }

  return TRUE;
}

static void
gst_detectionmetas_free (GstMeta * meta, GstBuffer * buffer)
{
}

const GstMetaInfo *
gst_detectionmetas_get_info (void)
{
  static const GstMetaInfo *meta_info = NULL;

  if (g_once_init_enter (&meta_info)) {
    const GstMetaInfo *meta =
      gst_meta_register (gst_detectionmetas_api_get_type (),
      "GstDetectionMetas",
      sizeof (GstDetectionMetas),
      gst_detectionmetas_init,
      gst_detectionmetas_free,
      gst_detectionmetas_transform);
    g_once_init_leave (&meta_info, meta);
  }

  return meta_info;
}